#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parse.h"
#include "util/list.h"
#include "util/unicode.h"

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

bool parse_document(stylesheet_t *stylesheet,
		struct parser_state *pstate, uint32_t ch) {
	struct parse_mode *mode = list_peek(pstate->modes);
	struct document_state *state = mode->state;
	if (!state) {
		state = calloc(sizeof(struct document_state), 1);
		mode->state = state;
		mode->destructor = document_state_free;
	}
	if (isspace(ch)) {
		continue;
	}
	return false;
}
