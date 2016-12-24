#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parse.h"
#include "util/list.h"
#include "util/unicode.h"

struct parse_mode *parse_mode_create(subparser_t parser) {
	struct parse_mode *pm = calloc(sizeof(struct parse_mode), 1);
	pm->parser = parser;
	pm->state = NULL;
	return pm;
}

void css_parse_ch(stylesheet_t *stylesheet,
		struct parser_state *state, uint32_t ch) {
	if (!state->modes) {
		state->modes = list_create();
	}
	if (state->modes->length == 0) {
		memset(&state->pending, 0, sizeof(state->pending));
		state->pending_head = state->pending_tail = 0;
		list_push(state->modes, parse_mode_create(parse_document));
	}

	state->pending[state->pending_head++] = ch;
	state->pending_head %= sizeof(state->pending) / sizeof(uint32_t);

	while (state->pending_tail != state->pending_head) {
		struct parse_mode *pm;
		pm = list_peek(state->modes);

		ch = state->pending[state->pending_tail++];
		state->pending_tail %= sizeof(state->pending) / sizeof(uint32_t);

		if (!(pm->flags & FLAG_WHITESPACE) && isspace(ch)) {
			continue;
		}

		if (!(pm->flags & FLAG_COMMENTS) && ch == '/') {
			if (state->pending_tail == state->pending_head) {
				--state->pending_tail;
				state->pending_tail %= sizeof(state->pending) / sizeof(uint32_t);
				break;
			}
			if (state->pending[state->pending_tail] == '*') {
				list_push(state->modes, parse_mode_create(parse_comment));
				++state->pending_tail;
				state->pending_tail %= sizeof(state->pending) / sizeof(uint32_t);
				continue;
			}
		}

		do {
			pm = list_peek(state->modes);
		} while (pm->parser(stylesheet, state, ch));
	}
}
