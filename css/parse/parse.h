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

#define FLAG_WHITESPACE 1
#define FLAG_COMMENTS 2

typedef bool (*subparser_t)(stylesheet_t *css,
		struct parser_state *pstate, uint32_t ch);

struct parse_mode {
	subparser_t parser;
	void (*destructor)(void *state);
	void *state;
	uint32_t flags;
};

void css_parse_ch(stylesheet_t *stylesheet,
		struct parser_state *state, uint32_t ch);

struct parse_mode *parse_mode_create(subparser_t);

bool parse_comment(stylesheet_t *stylesheet,
		struct parser_state *pstate, uint32_t ch);
bool parse_document(stylesheet_t *stylesheet,
		struct parser_state *pstate, uint32_t ch);

#endif
