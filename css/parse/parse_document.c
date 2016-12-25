#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parse.h"
#include "util/list.h"
#include "util/unicode.h"
#include "util/string.h"

struct document_state {
	str_t *selector;
	style_rule_t *style_rule;
	media_rule_t *media_rule;
	keyframes_t *keyframes;
};

static void document_state_free(void *_state) {
	struct document_state *state = _state;
	if (!state) return;
	str_free(state->selector);
	media_rule_free(state->media_rule);
	keyframes_free(state->keyframes);
	free(state);
}

static void commit_selector(struct document_state *state) {
	selector_t *selector = selector_parse(state->selector->str);
	if (!selector) {
		// TODO: error
		return;
	}
	if (!state->style_rule) {
		state->style_rule = calloc(sizeof(style_rule_t), 1);
	}
	if (!state->style_rule->selectors) {
		state->style_rule->selectors = list_create();
	}
	list_add(state->style_rule->selectors, selector);
	str_free(state->selector);
	state->selector = NULL;
}

static void parse_selector_ch(stylesheet_t *stylesheet,
	struct document_state *state, struct parser_state *pstate, uint32_t ch) {
	switch (ch) {
	case '{':
		commit_selector(state);
		// TODO: transition to parsing properties
		list_add(stylesheet->rules, state->style_rule);
		break;
	case ',':
		commit_selector(state);
		break;
	default:
		str_append_ch(state->selector, ch);
		break;
	}
}

void parse_document(stylesheet_t *stylesheet,
		struct parser_state *pstate, uint32_t ch) {
	struct subparser_state *subp = list_peek(pstate->parsers);
	struct document_state *state = subp->state;

	if (!state) {
		state = calloc(sizeof(struct document_state), 1);
		subp->state = state;
		subp->destructor = document_state_free;
	}

	if (!state->selector && !state->media_rule && !state->keyframes) {
		switch (ch) {
		case '@':
			// TODO: media/keyframes
			break;
		case '{':
			// TODO: error
			break;
		default:
			state->selector = str_create();
			subp->flags |= FLAG_WHITESPACE;
			break;
		}
	}

	if (state->selector) {
		parse_selector_ch(stylesheet, state, pstate, ch);
	}
}
