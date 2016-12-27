#ifndef _SUI_CSS_PARSE_H
#define _SUI_CSS_PARSE_H

#include <stdarg.h>
#include <stdint.h>
#include "util/list.h"
#include "util/errors.h"
#include "css.h"

struct parser_state {
	list_t *parsers;
	int pending_head, pending_tail;
	uint32_t pending[8];
	errors_t **errs;
	int lineno, colno;
};

#define FLAG_WHITESPACE 1
#define FLAG_COMMENTS 2
#define FLAG_WAIT 4

typedef void (*subparser_t)(stylesheet_t *css,
		struct parser_state *pstate, uint32_t ch);

struct subparser_state {
	subparser_t parser;
	void (*destructor)(void *state);
	void *state;
	uint32_t flags;
	uint32_t wait;
};

void css_parse_ch(stylesheet_t *stylesheet,
		struct parser_state *state, uint32_t ch);
void parser_state_cleanup(struct parser_state *state);

struct subparser_state *push_parser(struct parser_state *state,
		subparser_t parser);
void parser_state_append_ch(struct parser_state *state, uint32_t ch);
void parser_error(struct parser_state *state, const char *fmt, ...);

void parse_comment(stylesheet_t *stylesheet,
		struct parser_state *pstate, uint32_t ch);
void parse_document(stylesheet_t *stylesheet,
		struct parser_state *pstate, uint32_t ch);
void parse_properties(stylesheet_t *stylesheet,
		struct parser_state *pstate, uint32_t ch);
struct subparser_state *push_properties_parser(struct parser_state *state,
		style_rule_t *style_rule);

#endif
