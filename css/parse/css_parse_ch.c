#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parse.h"
#include "util/list.h"
#include "util/unicode.h"

static struct parse_mode *mode_create(bool (*handler)(stylesheet_t *stylesheet,
			struct parser_state *pstate, uint32_t ch)) {
	struct parse_mode *pm = malloc(sizeof(struct parse_mode));
	pm->handler = handler;
	pm->state = NULL;
	return pm;
}

static bool handle_comment(stylesheet_t *stylesheet,
		struct parser_state *pstate, uint32_t ch) {
	size_t previous = (pstate->pending_tail - 2) %
		(sizeof(pstate->pending) / sizeof(uint32_t));
	if (ch == '/' && pstate->pending[previous] == '*') {
		list_pop(pstate->modes);
	}
	return false;
}

struct document_state {
	style_rule_t *style_rule;
	media_rule_t *media_rule;
	keyframes_t *keyframes;
};

static void document_state_free(void *_state) {
	struct document_state *state = _state;
	if (!state) return;
	style_rule_free(state->style_rule);
	media_rule_free(state->media_rule);
	keyframes_free(state->keyframes);
	free(state);
}

static bool handle_document(stylesheet_t *stylesheet,
		struct parser_state *pstate, uint32_t ch) {
	struct parse_mode *mode = list_peek(pstate->modes);
	struct document_state *state = mode->state;
	if (!state) {
		state = calloc(sizeof(struct document_state), 1);
		mode->state = state;
		mode->destructor = document_state_free;
	}
	return false;
}

void css_parse_ch(stylesheet_t *stylesheet,
		struct parser_state *state, uint32_t ch) {
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
		} while (pm->handler(stylesheet, state, ch));
	}
}
