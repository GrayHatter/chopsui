#include <stdlib.h>
#include "parser.h"

void parser_pop(struct parser_state *state) {
	struct subparser_state *subparser = list_pop(state->parsers);
	if (subparser->destructor) {
		subparser->destructor(subparser->state);
	}
	free(subparser);
}
