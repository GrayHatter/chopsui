#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "util/list.h"
#include "util/errors.h"

const char *append_error(errors_t **errs, const char *fmt, ...) {
	if (!errs) {
		return NULL;
	}

	if (!*errs) {
		*errs = list_create();
	}

	va_list args;
	va_start(args, fmt);
	int len = vsnprintf(NULL, 0, fmt, args);
	va_end(args);

	char *buf = malloc(len + 1);
	va_start(args, fmt);
	vsnprintf(buf, len + 1, fmt, args);
	va_end(args);

	list_add(*errs, buf);
	return buf;
}

void errors_free(errors_t *errs) {
	for (size_t i = 0; errs && i < errs->length; ++i) {
		free(errs->items[i]);
	}
	free(errs);
}
