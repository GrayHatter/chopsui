#include <stdint.h>
#include "parser.h"

uint32_t parser_far_peek_ch(struct parser_state *state, int offs) {
	size_t i = (state->pending_tail + offs) %
		(sizeof(state->pending) / sizeof(uint32_t));
	return state->pending[i];
}
