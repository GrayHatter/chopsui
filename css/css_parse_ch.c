#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"
#include "subparser.h"
#include "util/list.h"

int css_parse_ch(struct parser_state *state, uint32_t ch) {
	struct subparser_state *subp;
	subp = list_peek(state->parsers);

	if ((subp->flags & FLAG_WAIT)) {
		if (ch == subp->wait) {
			subp->flags &= ~FLAG_WAIT;
		}
		return PARSER_SKIP;
	}

	if (!(subp->flags & FLAG_WHITESPACE) && isspace(ch)) {
		return PARSER_SKIP;
	}

	if (!(subp->flags & FLAG_COMMENTS) && ch == '/') {
		if (parser_buffer_empty(state)) {
			parser_push_ch(state, ch);
			return PARSER_DEFER;
		}
		if (parser_peek_ch(state) == '*') {
			parser_push(state, parse_comment, "css:comment");
			parser_pop_ch(state);
			return PARSER_SKIP;
		}
	}

	return PARSER_CONTINUE;
}
