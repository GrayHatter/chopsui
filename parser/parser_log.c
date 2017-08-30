#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "parser.h"

// TODO: make more robust

static void indent(int amt) {
	while (amt--) {
		fputs("  ", stderr);
	}
}

static bool parser_log_enabled() {
	const char *log = getenv("CHOPSUI_LOG");
	if (!log) {
		return false;
	}
	return strstr(log, "parser");
}

void parser_log(struct parser_state *pstate, const char *fmt, ...) {
	if (!parser_log_enabled()) {
		return;
	}
	int parsers = pstate->parsers->length;
	if (parsers) {
		struct subparser_state *subp = pstate->parsers->items[parsers - 1];
		indent(parsers - 1);
		fprintf(stderr, "[%s] ", subp->name);
	} else {
		fprintf(stderr, "[(null)] ");
	}
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fputc('\n', stderr);
}
