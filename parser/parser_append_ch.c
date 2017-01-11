#include <stdint.h>
#include "parser.h"

void parser_append_ch(struct parser_state *state, uint32_t ch) {
	state->pending[state->pending_head++] = ch;
	state->pending_head %= sizeof(state->pending) / sizeof(uint32_t);
}
