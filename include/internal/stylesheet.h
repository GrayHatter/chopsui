#ifndef _SUI_INTERNAL_STYLESHEET_H
#define _SUI_INTERNAL_STYLESHEET_H

#include <stdint.h>
#include "util/list.h"
#include "css.h"

struct parser_state {
	list_t *modes;
	int pending_head, pending_tail;
	uint32_t pending[8];
};

struct parse_mode {
	bool (*handler)(stylesheet_t *stylesheet, void *state, struct parser_state *pstate, uint32_t ch);
	void *state;
};

void stylesheet_parsec(stylesheet_t *stylesheet, struct parser_state *state,
		uint32_t ch);

#endif
