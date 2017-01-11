#ifndef _SUI_CSS_PARSE_H
#define _SUI_CSS_PARSE_H

#include <stdarg.h>
#include <stdint.h>
#include "parser.h"
#include "util/list.h"
#include "util/errors.h"
#include "css.h"

#define FLAG_WHITESPACE 1
#define FLAG_COMMENTS 2
#define FLAG_WAIT 4

int css_parse_ch(struct parser_state *state, uint32_t ch);

void parse_comment(struct parser_state *pstate, uint32_t ch);
void parse_document(struct parser_state *pstate, uint32_t ch);
void parse_properties(struct parser_state *pstate, uint32_t ch);

struct subparser_state *push_properties(struct parser_state *state,
		style_rule_t *style_rule);

#endif
