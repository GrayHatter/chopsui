#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "util/list.h"
#include "util/unicode.h"
#include "internal/stylesheet.h"

static struct parse_mode *mode_create(bool (*handler)(stylesheet_t *stylesheet,
		void *state, struct parser_state *pstate, uint32_t ch)) {
	struct parse_mode *pm = malloc(sizeof(struct parse_mode));
	pm->handler = handler;
	pm->state = NULL;
	return pm;
}

static bool handle_comment(stylesheet_t *stylesheet, void *state, struct
		parser_state *pstate, uint32_t ch) {
	size_t previous = (pstate->pending_tail - 2) %
		(sizeof(pstate->pending) / sizeof(uint32_t));
	if (ch == '/' && pstate->pending[previous] == '*') {
		list_pop(pstate->modes);
	}
	return false;
}

static bool handle_document(stylesheet_t *stylesheet, void *state, struct
		parser_state *pstate, uint32_t ch) {
	// TODO
	return false;
}

void stylesheet_parsec(stylesheet_t *stylesheet, struct parser_state *state,
		uint32_t ch) {
	if (!state->modes) {
		state->modes = list_create();
	}
	if (state->modes->length == 0) {
		memset(&state->pending, 0, sizeof(state->pending));
		state->pending_head = state->pending_tail = 0;
		list_push(state->modes, mode_create(handle_document));
	}

	state->pending[state->pending_head++] = ch;
	state->pending_head %= sizeof(state->pending) / sizeof(uint32_t);

	while (state->pending_tail != state->pending_head) {
		ch = state->pending[state->pending_tail++];
		state->pending_tail %= sizeof(state->pending) / sizeof(uint32_t);
		if (ch == '/') {
			if (state->pending_tail == state->pending_head) {
				--state->pending_tail;
				state->pending_tail %= sizeof(state->pending) / sizeof(uint32_t);
				break;
			}
			if (state->pending[state->pending_tail] == '*') {
				list_push(state->modes, mode_create(handle_comment));
				++state->pending_tail;
				state->pending_tail %= sizeof(state->pending) / sizeof(uint32_t);
				continue;
			}
		}
		struct parse_mode *pm;
		do {
			pm = list_peek(state->modes);
		} while (pm->handler(stylesheet, pm->state, state, ch));
	}
}
