#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parse.h"
#include "parser.h"
#include "util/list.h"
#include "util/errors.h"
#include "util/unicode.h"

void css_parse_ch(stylesheet_t *stylesheet,
		struct parser_state *state, uint32_t ch) {
	if (!state->parsers) {
		state->parsers = list_create();
	}
	if (state->parsers->length == 0) {
		memset(&state->pending, 0, sizeof(state->pending));
		state->pending_head = state->pending_tail = 0;
		state->lineno = state->colno = 1;
		parser_push(state, parse_document);
	}

	parser_append_ch(state, ch);

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
				parser_push(state, parse_comment);
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
