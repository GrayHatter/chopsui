#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parse.h"
#include "parser.h"
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
		if (state->pending_tail == state->pending_head) {
			--state->pending_tail;
			state->pending_tail %= sizeof(state->pending) / sizeof(uint32_t);
			return PARSER_DEFER;
		}
		if (state->pending[state->pending_tail] == '*') {
			parser_push(state, parse_comment);
			++state->pending_tail;
			state->pending_tail %= sizeof(state->pending) / sizeof(uint32_t);
			return PARSER_SKIP;
		}
	}

	return PARSER_CONTINUE;
}
