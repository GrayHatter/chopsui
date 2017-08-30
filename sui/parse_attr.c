#define _XOPEN_SOURCE 500
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "util/string.h"
#include "node.h"
#include "subparser.h"
#include "parser.h"
#include "scalars.h"

struct attr_state {
	char *key;
	char *val; // TODO: scalar
	void (*commit)(void *, const char *, void *);
	void *state;
	struct parser_state *pstate;
};

static void commit_key(void *_state, const char *str) {
	// TODO: validate characters used
	struct attr_state *state = _state;
	if (str) {
		state->key = strdup(str);
	}
}

static void commit_val(void *_state, const char *str) {
	struct attr_state *state = _state;
	if (!str) {
		parser_error(state->pstate, "Unspecified attribute value");
	}
	state->val = strdup(str);
	parser_pop(state->pstate);
}

static void attr_state_free(void *_state) {
	struct attr_state *state = _state;
	if (!state) return;
	if (state->key && state->commit) {
		struct sui_scalar *scalar = calloc(1, sizeof(struct sui_scalar));
		if (state->val) {
			scalar->type = SCALAR_STR;
			scalar->str = state->val;
		}
		parser_log(state->pstate, "commit %s=%s", state->key, scalar->str);
		state->commit(state->state, state->key, scalar);
	}
	free(state->key);
	free(state);
}

void parse_attr(struct parser_state *pstate, uint32_t ch) {
	struct subparser_state *subparser = list_peek(pstate->parsers);
	struct attr_state *state = subparser->state;

	if (isspace(ch)) {
		return;
	} else if (ch == '=') {
		if (!state->key) {
			parser_error(pstate, "Cannot specify attribute without key");
		} else {
			push_string_parser(pstate, state, commit_val);
		}
	} else if (!state->key) {
		push_string_parser(pstate, state, commit_key);
		parser_push_ch(pstate, ch);
	} else {
		parser_push_ch(pstate, ch);
		parser_pop(pstate);
	}
}

struct subparser_state *push_attr_parser(struct parser_state *pstate,
		void *state, void (*commit)(void *, const char *, void *)) {
	struct subparser_state *subparser = parser_push(
			pstate, parse_attr, "sui:attr");
	subparser->destructor = attr_state_free;
	struct attr_state *sstate = calloc(sizeof(struct attr_state), 1);
	sstate->state = state;
	sstate->pstate = pstate;
	sstate->commit = commit;
	subparser->state = sstate;
	return subparser;
}
