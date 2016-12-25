#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parse.h"
#include "util/list.h"
#include "util/unicode.h"

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
		push_parser(state, parse_document);
	}

	parser_state_append_ch(state, ch);

	while (state->pending_tail != state->pending_head) {
		struct subparser_state *subp;
		subp = list_peek(state->parsers);

		ch = state->pending[state->pending_tail++];
		state->pending_tail %= sizeof(state->pending) / sizeof(uint32_t);

		if (!(subp->flags & FLAG_WHITESPACE) && isspace(ch)) {
			continue;
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
				continue;
			}
		}

		subp->parser(stylesheet, state, ch);
	}
}
