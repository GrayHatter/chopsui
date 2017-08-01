#ifndef _SUI_SUI_SUBPARSER_H
#define _SUI_SUI_SUBPARSER_H

#include <stdint.h>
#include "parser.h"
#include "node.h"

#define FLAG_COMMENTS 1
#define FLAG_WAIT 2

enum indent_type {
	INDENT_UNKNOWN,
	INDENT_SPACES,
	INDENT_TABS
};

struct sui_parser_state {
	struct sui_node *root;
	int depth;
	int width;
	enum indent_type indent;
};

struct sui_node *sui_node_create();

int sui_parse_ch(struct parser_state *state, uint32_t ch);

void parse_node(struct parser_state *pstate, uint32_t ch);
void parse_string(struct parser_state *pstate, uint32_t ch);

struct subparser_state *push_string_parser(struct parser_state *pstate,
		void *state, void (*commit)(void *, const char *));
struct subparser_state *push_node_parser(struct parser_state *pstate,
		struct sui_node *parent);

#endif
