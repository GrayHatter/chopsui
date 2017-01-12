#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "parse.h"
#include "util/list.h"

void parse_comment(struct parser_state *pstate, uint32_t ch) {
	if (ch == '/' && parser_far_peek_ch(pstate, -2) == '*') {
		list_pop(pstate->parsers);
	}
}
