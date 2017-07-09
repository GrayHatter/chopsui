#include <stdint.h>
#include "parser.h"

void parser_push_ch(struct parser_state *state, uint32_t ch, bool original) {
	state->pending[state->pending_head++] = ch;
	state->pending_head %= sizeof(state->pending) / sizeof(uint32_t);
	if (!original) {
		if (ch == '\n') {
			--state->lineno;
			state->colno = 1;
		} else {
			--state->colno;
		}
	}
}
