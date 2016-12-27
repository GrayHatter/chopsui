#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parse.h"
#include "util/list.h"
#include "util/errors.h"
#include "util/unicode.h"

void parser_error(struct parser_state *state, const char *fmt, ...) {
	char staticbuf[256];

	if (!state->errs) {
		return;
	}

	va_list args;
	va_start(args, fmt);
	int len = vsnprintf(NULL, 0, fmt, args);
	va_end(args);

	char *buf;

	if (len + 1 <= 256) {
		buf = staticbuf;
	} else {
		buf = malloc(len + 1);
	}

	va_start(args, fmt);
	vsnprintf(buf, len + 1, fmt, args);
	va_end(args);

	append_error(state->errs, "[%d:%d] %s",
			state->lineno, state->colno, buf);

	if (len + 1 > 256) {
		free(buf);
	}
}

struct subparser_state *push_parser(struct parser_state *state,
		subparser_t parser) {
	struct subparser_state *subp = calloc(sizeof(struct subparser_state), 1);
	subp->parser = parser;
	subp->state = NULL;
	list_push(state->parsers, subp);
	return subp;
}

void parser_state_append_ch(struct parser_state *state, uint32_t ch) {
	state->pending[state->pending_head++] = ch;
	state->pending_head %= sizeof(state->pending) / sizeof(uint32_t);
}

void parser_state_cleanup(struct parser_state *state) {
	if (!state->parsers) {
		return;
	}
	for (size_t i = 0; i < state->parsers->length; ++i) {
		struct subparser_state *s = state->parsers->items[i];
		if (s->destructor) {
			s->destructor(s->state);
		}
		free(s);
	}
	list_free(state->parsers);
}

void css_parse_ch(stylesheet_t *stylesheet,
		struct parser_state *state, uint32_t ch) {
	if (!state->parsers) {
		state->parsers = list_create();
	}
	if (state->parsers->length == 0) {
		memset(&state->pending, 0, sizeof(state->pending));
		state->pending_head = state->pending_tail = 0;
		state->lineno = state->colno = 1;
		push_parser(state, parse_document);
	}

	parser_state_append_ch(state, ch);

	while (state->pending_tail != state->pending_head) {
		struct subparser_state *subp;
		subp = list_peek(state->parsers);

		ch = state->pending[state->pending_tail++];
		state->pending_tail %= sizeof(state->pending) / sizeof(uint32_t);

		if ((subp->flags & FLAG_WAIT)) {
			if (ch == subp->wait) {
				subp->flags &= ~FLAG_WAIT;
			}
			goto loop_cont;
		}

		if (!(subp->flags & FLAG_WHITESPACE) && isspace(ch)) {
			goto loop_cont;
		}

		if (!(subp->flags & FLAG_COMMENTS) && ch == '/') {
			if (state->pending_tail == state->pending_head) {
				--state->pending_tail;
				state->pending_tail %= sizeof(state->pending) / sizeof(uint32_t);
				break;
			}
			if (state->pending[state->pending_tail] == '*') {
				push_parser(state, parse_comment);
				++state->pending_tail;
				state->pending_tail %= sizeof(state->pending) / sizeof(uint32_t);
				goto loop_cont;
			}
		}

		subp->parser(stylesheet, state, ch);

loop_cont:
		if (ch == '\n') {
			++state->lineno;
			state->colno = 1;
		} else {
			++state->colno;
		}
	}
}
