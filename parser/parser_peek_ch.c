#include <stdint.h>
#include "parser.h"

uint32_t parser_peek_ch(struct parser_state *state) {
	return state->pending[state->pending_tail];
}
