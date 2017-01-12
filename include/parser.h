#ifndef _SUI_PARSER_H
#define _SUI_PARSER_H

#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>
#include "util/errors.h"
#include "util/list.h"

#define PARSER_SKIP 1
#define PARSER_DEFER 2
#define PARSER_CONTINUE 3

struct parser_state {
	list_t *parsers;
	int pending_head, pending_tail;
	uint32_t pending[64];
	errors_t **errs;
	int lineno, colno;
	void *data;
	int (*iter)(struct parser_state *, uint32_t);
};

typedef void (*subparser_t)(struct parser_state *pstate, uint32_t ch);

typedef int (*parser_iter_t)(struct parser_state *pstate, uint32_t ch);

struct subparser_state {
	subparser_t parser;
	void (*destructor)(void *state);
	void *state;
	uint32_t flags;
	uint32_t wait;
};

void parser_error(struct parser_state *state, const char *fmt, ...);
void parser_cleanup(struct parser_state *state);
struct subparser_state *parser_push(struct parser_state *state,
		subparser_t parser);
void parser_pop(struct parser_state *state);
void parser_push_ch(struct parser_state *state, uint32_t ch);
uint32_t parser_pop_ch(struct parser_state *state);
uint32_t parser_peek_ch(struct parser_state *state);
uint32_t parser_far_peek_ch(struct parser_state *state, int offs);
bool parser_buffer_empty(struct parser_state *state);

/*
 * Initializes the parser state, sets the initial parser as specified, and
 * configures the grammar-specific iter function.
 */
void parser_init(struct parser_state *state, subparser_t initial_parser,
		parser_iter_t iter);

/*
 * Runs one iteration of the parser loop with the given character. Will invoke
 * the grammar-specific iter function for each character processed, which can
 * return one of PARSER_SKIP, PARSER_DEFER, or PARSER_CONTINUE. PARSER_SKIP
 * skips the subparser, PARSER_DEFER leaves the loop and defers the character
 * for later processing, and PARSER_CONTINUE continues normally.
 */
void parse_ch(struct parser_state *state, uint32_t ch);

#endif
