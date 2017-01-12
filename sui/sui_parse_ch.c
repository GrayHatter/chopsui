#include <stdint.h>
#include "parser.h"
#include "subparser.h"
#include "util/list.h"

int sui_parse_ch(struct parser_state *state, uint32_t ch) {
	struct subparser_state *subp;
	subp = list_peek(state->parsers);

	if ((subp->flags & FLAG_WAIT)) {
		if (ch == subp->wait) {
			subp->flags &= ~FLAG_WAIT;
		}
		return PARSER_SKIP;
	}

	if (!(subp->flags & FLAG_COMMENTS) && ch == '#') {
		subp->wait = '\n';
		subp->flags |= FLAG_WAIT;
		return PARSER_SKIP;
	}

	return PARSER_CONTINUE;
}
