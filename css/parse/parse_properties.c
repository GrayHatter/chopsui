#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parse.h"
#include "util/list.h"
#include "util/unicode.h"
#include "util/string.h"

struct properties_state {
	style_rule_t *style_rule;
	str_t *key, *value;
};

struct subparser_state *push_properties_parser(struct parser_state *state,
		style_rule_t *style_rule) {
	struct subparser_state *subparser = push_parser(state,
			parse_properties);
	struct properties_state *pstate = calloc(sizeof(struct properties_state), 1);
	pstate->style_rule = style_rule;
	subparser->state = pstate;
	return subparser;
}

void parse_properties(stylesheet_t *stylesheet,
		struct parser_state *pstate, uint32_t ch) {
	struct subparser_state *subparser = list_peek(pstate->parsers);
	struct properties_state *state = subparser->state;
	switch (ch) {
	case '}':
		list_add(stylesheet->rules, state->style_rule);
		list_pop(pstate->parsers);
		break;
	}
}
