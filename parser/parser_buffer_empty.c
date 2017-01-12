#include <stdint.h>
#include "parser.h"

bool parser_buffer_empty(struct parser_state *state) {
	return state->pending_tail == state->pending_head;
}
