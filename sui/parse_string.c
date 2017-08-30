#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "util/string.h"
#include "node.h"
#include "subparser.h"
#include "parser.h"

enum string_type {
	STRING_LITERAL,
	STRING_DOUBLE_QUOTE,
	STRING_SINGLE_QUOTE
};

struct string_state {
	str_t *str;
	enum string_type type;
	void (*commit)(void *, const char *);
	void *state;
	struct parser_state *pstate;
};

void string_state_free(void *_state) {
	struct string_state *state = _state;
	if (!state) return;
	if (state->str && state->commit) {
		// Commit the string at EOF
		state->commit(state->state, state->str->str);
	}
	str_free(state->str);
	free(state);
}

struct subparser_state *push_string_parser(struct parser_state *pstate,
		void *state, void (*commit)(void *, const char *)) {
	struct subparser_state *subparser = parser_push(
			pstate, parse_string, "sui:string");
	subparser->destructor = string_state_free;
	struct string_state *sstate = calloc(sizeof(struct string_state), 1);
	sstate->state = state;
	sstate->pstate = pstate;
	sstate->commit = commit;
	subparser->state = sstate;
	return subparser;
}

void parse_string(struct parser_state *pstate, uint32_t ch) {
	struct subparser_state *subparser = list_peek(pstate->parsers);
	struct string_state *state = subparser->state;
	if (!state->str) {
		state->str = str_create();
		switch (ch) {
		case '"':
			state->type = STRING_DOUBLE_QUOTE;
			return;
		case '\'':
			state->type = STRING_SINGLE_QUOTE;
			return;
		default:
			state->type = STRING_LITERAL;
			break;
		}
	}

	bool commit = false;
	switch (state->type) {
	case STRING_DOUBLE_QUOTE:
		commit = ch == '"';
		break;
	case STRING_SINGLE_QUOTE:
		commit = ch == '\'';
		break;
	default:
		commit = isspace(ch) || strchr(".@=[{}]", ch);
	}

	if (commit) {
		parser_pop(pstate);
		parser_push_ch(pstate, ch);
	} else {
		str_append_ch(state->str, ch);
	}
}
