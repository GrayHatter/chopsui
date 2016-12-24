#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "parse.h"
#include "util/list.h"

void parse_comment(stylesheet_t *stylesheet,
		struct parser_state *pstate, uint32_t ch) {
	size_t previous = (pstate->pending_tail - 2) %
		(sizeof(pstate->pending) / sizeof(uint32_t));
	if (ch == '/' && pstate->pending[previous] == '*') {
		list_pop(pstate->parsers);
	}
}
