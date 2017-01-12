#ifndef _SUI_SUI_SUBPARSER_H
#define _SUI_SUI_SUBPARSER_H

#include <stdint.h>
#include "parser.h"
#include "node.h"

#define FLAG_COMMENTS 1

struct sui_parser_state {
	sui_node_t *node;
	size_t depth;
};

sui_node_t *sui_node_create();

int sui_parse_ch(struct parser_state *state, uint32_t ch);

void parse_node(struct parser_state *pstate, uint32_t ch);

#endif
