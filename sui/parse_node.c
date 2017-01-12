#define _XOPEN_SOURCE 500
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "tree.h"
#include "subparser.h"

static void commit_type(struct parser_state *pstate, const char *str) {
	struct sui_parser_state *state = pstate->data;
	if (state->node->type) {
		parser_error(pstate, "Node cannot have two types");
	} else {
		state->node->type = strdup(str);
	}
}

static void commit_id(struct parser_state *pstate, const char *str) {
	struct sui_parser_state *state = pstate->data;
	if (state->node->id) {
		parser_error(pstate, "Node cannot have two IDs");
	} else {
		state->node->id = strdup(str);
	}
}

static void commit_class(struct parser_state *pstate, const char *str) {
	struct sui_parser_state *state = pstate->data;
	node_add_class(state->node, str);
}

void parse_node(struct parser_state *pstate, uint32_t ch) {
	struct sui_parser_state *state = pstate->data;
	if (!state->node) {
		switch (ch) {
		case '\t':
		case ' ':
			// TODO: depth
			break;
		case '\n':
			// TODO
			break;
		default:
			// Start new node and parse type
			state->node = sui_node_create();
			push_string_parser(pstate, commit_type);
			parser_push_ch(pstate, ch);
			break;
		}
	} else {
		switch (ch) {
		case '\t':
		case ' ':
			// Ignore whitespace
			break;
		case '\n':
		case ',':
			// TODO: Commit this node to the parent
			break;
		case '.':
			push_string_parser(pstate, commit_class);
			break;
		case '@':
			push_string_parser(pstate, commit_id);
			break;
		case '[':
			// TODO:
			// push_attributes_parser(pstate);
			break;
		case '{':
			// TODO:
			// Parse inline children
			break;
		default:
			// TODO:
			// push_attribute_parser(pstate);
			// parser_push_ch(pstate, ch);
			break;
		}
	}
}
