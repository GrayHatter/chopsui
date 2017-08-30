#include <stdlib.h>
#include "util/list.h"
#include "parser.h"

struct subparser_state *parser_push(struct parser_state *state,
		subparser_t parser, const char *name) {
	struct subparser_state *subp = calloc(sizeof(struct subparser_state), 1);
	subp->parser = parser;
	subp->state = NULL;
	subp->name = name;
	parser_log(state, "parser_push %s", name);
	list_push(state->parsers, subp);
	return subp;
}
