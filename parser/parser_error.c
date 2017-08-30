#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "util/errors.h"
#include "parser.h"

void parser_error(struct parser_state *state, const char *fmt, ...) {
	char staticbuf[256];

	if (!state->errs) {
		return;
	}

	va_list args;
	va_start(args, fmt);
	int len = vsnprintf(NULL, 0, fmt, args);
	va_end(args);

	char *buf;

	if (len + 1 <= 256) {
		buf = staticbuf;
	} else {
		buf = malloc(len + 1);
	}

	va_start(args, fmt);
	vsnprintf(buf, len + 1, fmt, args);
	va_end(args);

	const char *err = append_error(state->errs, "[%d:%d] %s",
			state->lineno, state->colno, buf);
	parser_log(state, "%s", err);

	if (len + 1 > 256) {
		free(buf);
	}
}
