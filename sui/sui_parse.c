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

sui_node_t *sui_parse(const char *source, errors_t **errs) {
	struct sui_parser_state sui_state = {
		.root = NULL,
		.parent = NULL,
		.node = NULL,
		.depth = 0,
		.width = -1,
		.indent = INDENT_UNKNOWN
	};

	struct parser_state state;
	memset(&state, 0, sizeof(state));
	state.errs = errs;
	state.data = &sui_state;
	parser_init(&state, sui_parse_ch);
	parser_push(&state, parse_node);

	while (*source) {
		uint32_t ch = utf8_decode(&source);
		parse_ch(&state, ch);
	}

	parser_cleanup(&state);

	if (!sui_state.root) {
		parser_error(&state, "No valid nodes found");
	}
	if (sui_state.node && sui_state.parent) {
		node_append_child(sui_state.parent, sui_state.node);
	}

	return sui_state.root;
}
