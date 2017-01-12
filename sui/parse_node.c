#define _XOPEN_SOURCE 500
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "tree.h"
#include "subparser.h"

static void commit_type(struct parser_state *pstate, const char *str) {
	struct sui_parser_state *state = pstate->data;
	state->node->type = strdup(str);
}

void parse_node(struct parser_state *pstate, uint32_t ch) {
	struct sui_parser_state *state = pstate->data;
	if (!state->node) {
		if (ch == '\t' || ch == ' ') {
			// TODO: depth
		} else {
			state->node = sui_node_create();
			push_string_parser(pstate, commit_type);
			parser_push_ch(pstate, ch);
		}
	}
}
