#ifndef _SUI_CSS_PARSE_H
#define _SUI_CSS_PARSE_H

#include <stdint.h>
#include "util/list.h"
#include "css.h"

struct parser_state {
	list_t *modes;
	int pending_head, pending_tail;
	uint32_t pending[8];
};

struct parse_mode {
	bool (*handler)(stylesheet_t *stylesheet, struct parser_state *pstate, uint32_t ch);
	void (*destructor)(void *state);
	void *state;
};

void css_parse_ch(stylesheet_t *stylesheet, struct parser_state *state,
		uint32_t ch);

#endif
