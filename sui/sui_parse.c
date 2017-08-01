#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "sui.h"
#include "node.h"
#include "tree.h"
#include "subparser.h"
#include "util/errors.h"
#include "util/unicode.h"

struct sui_node *sui_parse(const char *source, errors_t **errs) {
	struct sui_parser_state sui_state = {
		.root = NULL,
		.depth = 0,
		.width = -1,
		.indent = INDENT_UNKNOWN
	};

	struct parser_state state;
	memset(&state, 0, sizeof(state));
	state.errs = errs;
	state.data = &sui_state;
	parser_init(&state, sui_parse_ch);
	push_node_parser(&state, NULL);

	while (*source) {
		uint32_t ch = utf8_decode(&source);
		parse_ch(&state, ch);
	}

	parser_cleanup(&state);

	if (!sui_state.root) {
		parser_error(&state, "No valid nodes found");
	}

	return sui_state.root;
}
