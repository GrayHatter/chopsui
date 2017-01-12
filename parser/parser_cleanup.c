#include <stddef.h>
#include <stdlib.h>
#include "util/list.h"
#include "parser.h"

void parser_cleanup(struct parser_state *state) {
	if (!state->parsers) {
		return;
	}
	for (int i = state->parsers->length - 1; i >= 0; --i) {
		struct subparser_state *s = state->parsers->items[i];
		if (s->destructor) {
			s->destructor(s->state);
		}
		free(s);
	}
	list_free(state->parsers);
}
