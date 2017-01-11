#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "util/list.h"

void parser_init(struct parser_state *state, subparser_t initial_parser,
		parser_iter_t iter) {
	state->parsers = list_create();
	memset(&state->pending, 0, sizeof(state->pending));
	state->pending_head = state->pending_tail = 0;
	state->lineno = state->colno = 1;
	state->iter = iter;
	parser_push(state, initial_parser);
}
