#define _XOPEN_SOURCE 500
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "tree.h"
#include "subparser.h"

struct node_state {
	size_t depth;
};

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

static void push_indent(struct sui_parser_state *state,
		struct parser_state *pstate, int depth) {
	while (depth--) {
		for (int i = 0; i < state->width; ++i) {
			parser_push_ch(pstate, state->indent == INDENT_SPACES ? ' ' : '\t');
		}
	}
}

void parse_node(struct parser_state *pstate, uint32_t ch) {
	struct subparser_state *subparser = list_peek(pstate->parsers);
	struct sui_parser_state *state = pstate->data;
	struct node_state *nstate = subparser->state;
	if (!nstate) {
		nstate = calloc(sizeof(*nstate), 1);
		subparser->state = nstate;
	}

	if (!state->node) {
		switch (ch) {
		case '\t':
			if (state->indent == INDENT_UNKNOWN) {
				state->indent = INDENT_TABS;
			}
			if (state->indent == INDENT_SPACES) {
				parser_error(pstate, "Mixed tabs and spaces are not permitted");
			}
			++nstate->depth;
			break;
		case ' ':
			if (state->indent == INDENT_UNKNOWN) {
				state->indent = INDENT_SPACES;
			}
			if (state->indent == INDENT_TABS) {
				parser_error(pstate, "Mixed tabs and spaces are not permitted");
			}
			++nstate->depth;
			break;
		case '\n':
			nstate->depth = 0;
			break;
		default:
			if (nstate->depth == 0) {
				if (state->root) {
					parser_error(pstate, "Cannot have two root nodes");
				} else {
					state->node = sui_node_create();
					state->root = state->node;
					push_string_parser(pstate, commit_type);
					parser_push_ch(pstate, ch);
				}
			} else {
				if (state->width == -1) {
					state->width = nstate->depth;
				}
				int depth = nstate->depth / state->width;
				if (nstate->depth % state->width) {
					parser_error(pstate,
							"Inconsistent indentation width is not permitted");
				}
				if (depth < state->depth) {
					push_indent(state, pstate, depth);
					parser_push_ch(pstate, ch);
					state->parent = state->parent->parent;
					state->node = NULL;
					--state->depth;
					parser_pop(pstate);
				} else if (depth > state->depth) {
					if (depth != state->depth + 1) {
						parser_error(pstate,
								"Multiple indents where one was expected");
					}
					// Child
					if (state->parent) {
						state->parent = state->parent->children->items[
							state->parent->children->length - 1];
					} else {
						state->parent = state->root;
					}
					nstate->depth = 0;
					state->depth = depth;
					state->node = NULL;
					push_indent(state, pstate, depth);
					parser_push_ch(pstate, ch);
					parser_push(pstate, parse_node);
				} else {
					// Sibling
					state->node = sui_node_create();
					push_string_parser(pstate, commit_type);
					parser_push_ch(pstate, ch);
				}
			}
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
			if (state->parent) {
				node_append_child(state->parent, state->node);
			}
			state->node = NULL;
			nstate->depth = 0;
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
