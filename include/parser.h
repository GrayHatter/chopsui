#ifndef _SUI_PARSER_H
#define _SUI_PARSER_H

#include <stdarg.h>
#include <stdint.h>
#include "util/errors.h"
#include "util/list.h"

struct parser_state {
	list_t *parsers;
	int pending_head, pending_tail;
	uint32_t pending[8];
	errors_t **errs;
	int lineno, colno;
	void *data;
};

typedef void (*subparser_t)(void *data,
		struct parser_state *pstate, uint32_t ch);

struct subparser_state {
	subparser_t parser;
	void (*destructor)(void *state);
	void *state;
	uint32_t flags;
	uint32_t wait;
};

void parser_error(struct parser_state *state, const char *fmt, ...);
struct subparser_state *parser_push(struct parser_state *state,
		subparser_t parser);
void parser_append_ch(struct parser_state *state, uint32_t ch);
void parser_cleanup(struct parser_state *state);

#endif
