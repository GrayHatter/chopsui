#define _XOPEN_SOURCE 500
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "tree.h"
#include "subparser.h"

struct node_state {
	size_t depth;
	struct parser_state *pstate;
	struct sui_node *parent;
	struct sui_node *node;
};

static void node_state_free(void *_state) {
	struct node_state *state = _state;
	if (!state) return;
	if (!state->node) return;
	if (state->parent) {
		node_append_child(state->parent, state->node);
		parser_log(state->pstate, "committing node");
	}
	free(state);
}

struct subparser_state *push_node_parser(struct parser_state *pstate,
		struct sui_node *parent) {
	struct subparser_state *subp = parser_push(
			pstate, parse_node, "sui:node");
	struct node_state *state = calloc(sizeof(struct node_state), 1);
	state->parent = parent;
	state->pstate = pstate;
	subp->state = state;
	subp->destructor = node_state_free;
	return subp;
}

static void push_indent(struct sui_parser_state *state,
		struct parser_state *pstate, int depth) {
	while (depth--) {
		for (int i = 0; i < state->width; ++i) {
			parser_push_ch(pstate, state->indent == INDENT_SPACES ? ' ' : '\t');
		}
	}
}

static void commit_type(void *_state, const char *str) {
	struct node_state *state = _state;
	if (state->node->type) {
		parser_error(state->pstate, "Node cannot have two types");
	} else {
		state->node->type = strdup(str);
		parser_log(state->pstate, "commit type='%s'", str);
	}
}

static void commit_id(void *_state, const char *str) {
	struct node_state *state = _state;
	if (state->node->id) {
		parser_error(state->pstate, "Node cannot have two IDs");
	} else {
		state->node->id = strdup(str);
		parser_log(state->pstate, "commit id='%s'", str);
	}
}

static void commit_class(void *_state, const char *str) {
	struct node_state *state = _state;
	node_add_class(state->node, str);
	parser_log(state->pstate, "commit class+='%s'", str);
}

static void commit_attrib(void *_state, const char *key, void *val) {
	struct node_state *state = _state;
	hashtable_set(state->node->attributes, key, val);
	parser_log(state->pstate, "commit attribute '%s'", key);
}

void parse_node(struct parser_state *pstate, uint32_t ch) {
	struct subparser_state *subparser = list_peek(pstate->parsers);
	struct sui_parser_state *sui_state = pstate->data;
	struct node_state *state = subparser->state;

	if (!state->node) {
		switch (ch) {
		case '\t':
			if (sui_state->indent == INDENT_UNKNOWN) {
				sui_state->indent = INDENT_TABS;
			}
			if (sui_state->indent == INDENT_SPACES) {
				parser_error(pstate, "Mixed tabs and spaces are not permitted");
			}
			++state->depth;
			break;
		case ' ':
			if (sui_state->indent == INDENT_UNKNOWN) {
				sui_state->indent = INDENT_SPACES;
			}
			if (sui_state->indent == INDENT_TABS) {
				parser_error(pstate, "Mixed tabs and spaces are not permitted");
			}
			++state->depth;
			break;
		case '\n':
			state->depth = 0;
			break;
		default:
			if (state->depth == 0) {
				if (sui_state->root) {
					parser_error(pstate, "Cannot have two root nodes");
				} else {
					state->node = sui_node_create();
					sui_state->root = state->node;
					push_string_parser(pstate, state, commit_type);
					parser_push_ch(pstate, ch);
				}
			} else {
				if (sui_state->width == -1) {
					sui_state->width = state->depth;
				}
				int depth = state->depth / sui_state->width;
				if (state->depth % sui_state->width) {
					parser_error(pstate,
							"Inconsistent indentation width is not permitted");
				}
				if (depth < sui_state->depth) {
					push_indent(sui_state, pstate, depth);
					parser_push_ch(pstate, ch);
					--sui_state->depth;
					parser_pop(pstate);
				} else if (depth > sui_state->depth) {
					if (depth != sui_state->depth + 1) {
						parser_error(pstate,
								"Multiple indents where one was expected");
					}
					// Child
					struct sui_node *parent;
					if (state->parent) {
						parent = list_peek(state->parent->children);
					} else {
						parent = sui_state->root;
					}
					state->depth = 0;
					sui_state->depth = depth;
					push_indent(sui_state, pstate, depth);
					parser_push_ch(pstate, ch);
					push_node_parser(pstate, parent);
				} else {
					// Sibling
					state->node = sui_node_create();
					push_string_parser(pstate, state, commit_type);
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
				parser_log(pstate, "committing node without pop");
				node_append_child(state->parent, state->node);
			}
			state->node = NULL;
			if (ch == ',') {
				// We want to reuse depth in this case
				subparser->flags |= FLAG_WHITESPACE;
			} else {
				state->depth = 0;
			}
			break;
		case '.':
			push_string_parser(pstate, state, commit_class);
			break;
		case '@':
			push_string_parser(pstate, state, commit_id);
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
			push_attr_parser(pstate, state, commit_attrib);
			parser_push_ch(pstate, ch);
			break;
		}
	}
}
