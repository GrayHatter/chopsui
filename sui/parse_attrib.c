#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "util/string.h"
#include "node.h"
#include "subparser.h"
#include "parser.h"
#include "scalars.h"

enum string_type {
	STRING_LITERAL,
	STRING_DOUBLE_QUOTE,
	STRING_SINGLE_QUOTE
};

enum phase {
	PHASE_UNKNOWN,
	PHASE_ATTRIB_KEY,
	PHASE_ATTRIB_READY,
	PHASE_ATTRIB_ASSIGN,
	PHASE_ATTRIB_VAL,
	PHASE_ATTRIB_DONE,
};

struct attrib_state {
	str_t *key;
	str_t *val; // TODO MAKE SCALAR
	enum phase phase;
	enum string_type type;
	void (*commit)(void *, const char *, void *);
	void *state;
	struct parser_state *pstate;
};

static void attrib_state_free(void *_state) {
	struct attrib_state *state = _state;
	if (!state) return;
	if (state->key && state->commit) {
		// Commit the string at EOF
		struct sui_scalar *scalar = calloc(1, sizeof(struct sui_scalar));
		if (state->val) {
			scalar->type = SCALAR_CHAR;
			scalar->str = calloc(1, state->val->size);
			memcpy(scalar->str, state->val->str, state->val->size);
		}

		state->commit(state->state, state->key->str, scalar);
	}
	str_free(state->key);
	str_free(state->val); // TODO THIS IS WRONG
	free(state);
}

static bool parse_attrib_key(struct attrib_state *state, uint32_t ch){
	if (!state->key) {
		state->key = str_create();
		switch (ch) {
		case '"':
			state->type = STRING_DOUBLE_QUOTE;
			return false;
		case '\'':
			state->type = STRING_SINGLE_QUOTE;
			return false;
		default:
			state->type = STRING_LITERAL;
		}
	}

	if (state->type == STRING_DOUBLE_QUOTE && ch == '"') {
		return true;
	}

	if (state->type == STRING_SINGLE_QUOTE && ch == '\'') {
		return true;
	}

	if (isspace(ch) || strchr(".@=[{}]", ch)) {
		return true;
	}

	str_append_ch(state->key, ch);
	return false;
}

static bool parse_attrib_val(struct attrib_state *state, uint32_t ch) {
	if (!state->val) {
		state->val = str_create();
		switch (ch) {
		case '"':
			state->type = STRING_DOUBLE_QUOTE;
			return false;
		case '\'':
			state->type = STRING_SINGLE_QUOTE;
			return false;
		default:
			state->type = STRING_LITERAL;
		}
	}

	if (state->type == STRING_DOUBLE_QUOTE && ch == '"') {
		return true;
	}

	if (state->type == STRING_SINGLE_QUOTE && ch == '\'') {
		return true;
	}

	if (isspace(ch) || strchr(".@=[{}]", ch)) {
		return true;
	}

	str_append_ch(state->val, ch);
	return false;
}

void parse_attrib(struct parser_state *pstate, uint32_t ch) {
	struct subparser_state *subparser = list_peek(pstate->parsers);
	struct attrib_state *state = subparser->state;

	switch(state->phase) {
	case PHASE_UNKNOWN:
		state->phase = PHASE_ATTRIB_KEY;
		/* fallthrough */
	case PHASE_ATTRIB_KEY:
		if (parse_attrib_key(state, ch)) {
			state->phase = PHASE_ATTRIB_READY;
			parser_push_ch(pstate, ch);
		}
		break;
	case PHASE_ATTRIB_READY:
		if (isspace(ch)) {
			return;
		}
		if (strchr("=", ch)) {
			state->phase = PHASE_ATTRIB_ASSIGN;
			return;
		}
		parser_pop(pstate);
		parser_push_ch(pstate, ch);
		return;
	case PHASE_ATTRIB_ASSIGN:
		if (isspace(ch)) {
			return;
		}
		state->phase = PHASE_ATTRIB_VAL;
		/* fallthrough */
	case PHASE_ATTRIB_VAL:
		if (parse_attrib_val(state, ch)) {
			parser_pop(pstate);
			parser_push_ch(pstate, ch);
		}
		break;
	default: // TODO handle error case?
		break;
	}
}

struct subparser_state *push_attrib_parser(struct parser_state *pstate,
		void *state, void (*commit)(void *, const char *, void *)) {
	struct subparser_state *subparser = parser_push(pstate, parse_attrib);
	subparser->destructor = attrib_state_free;
	struct attrib_state *sstate = calloc(sizeof(struct attrib_state), 1);
	sstate->state = state;
	sstate->pstate = pstate;
	sstate->commit = commit;
	subparser->state = sstate;
	return subparser;
}
