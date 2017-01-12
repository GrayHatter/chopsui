#include <stdint.h>
#include "parser.h"
#include "util/list.h"

void parse_ch(struct parser_state *state, uint32_t ch) {
	parser_push_ch(state, ch);

	while (state->pending_tail != state->pending_head) {
		struct subparser_state *subp;

		subp = list_peek(state->parsers);
		ch = parser_pop_ch(state);

		int r = state->iter(state, ch);
		if (r == PARSER_CONTINUE) {
			subp->parser(state, ch);
		} else if (r == PARSER_DEFER) {
			break;
		}

		if (ch == '\n') {
			++state->lineno;
			state->colno = 1;
		} else {
			++state->colno;
		}
	}
}