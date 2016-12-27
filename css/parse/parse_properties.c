#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parse.h"
#include "util/list.h"
#include "util/hashtable.h"
#include "util/unicode.h"
#include "util/string.h"

struct properties_state {
	style_rule_t *style_rule;
	str_t *key, *value;
};

static void properties_state_free(void *_state) {
	struct properties_state *state = _state;
	if (!state) return;
	style_rule_free(state->style_rule);
	str_free(state->key);
	str_free(state->value);
	free(state);
}

struct subparser_state *push_properties_parser(struct parser_state *state,
		style_rule_t *style_rule) {
	struct subparser_state *subparser = push_parser(state,
			parse_properties);
	subparser->destructor = properties_state_free;
	struct properties_state *pstate = calloc(sizeof(struct properties_state), 1);
	pstate->style_rule = style_rule;
	pstate->key = str_create();
	subparser->state = pstate;
	return subparser;
}

void parse_properties(stylesheet_t *stylesheet,
		struct parser_state *pstate, uint32_t ch) {
	struct subparser_state *subparser = list_peek(pstate->parsers);
	struct properties_state *state = subparser->state;
	switch (ch) {
	case ':':
		if (state->value) {
			// TODO: error
		} else {
			state->value = str_create();
		}
		break;
	case ';':
		if (!state->value || !state->key) {
			// TODO: error
		} else {
			hashtable_set(state->style_rule->properties,
					state->key->str, state->value->str);
			free(state->key);
			free(state->value);
			state->key = str_create();
			state->value = NULL;
		}
		break;
	case '}':
		list_add(stylesheet->rules, state->style_rule);
		list_pop(pstate->parsers);
		break;
	case '\'': // Fallthrough
	case '"':
		// TODO
		break;
	default:
		if (state->value) {
			str_append_ch(state->value, ch);
		} else {
			str_append_ch(state->key, ch);
		}
		break;
	}
}
