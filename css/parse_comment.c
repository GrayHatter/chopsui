#include <stdint.h>
#include "subparser.h"
#include "util/list.h"

void parse_comment(struct parser_state *pstate, uint32_t ch) {
	if (ch == '/' && parser_far_peek_ch(pstate, -2) == '*') {
		parser_pop(pstate);
	}
}
