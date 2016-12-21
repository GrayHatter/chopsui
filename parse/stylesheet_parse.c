#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "util/list.h"
#include "util/unicode.h"
#include "internal/stylesheet.h"

stylesheet_t *stylesheet_parse(const char *source) {
	stylesheet_t *stylesheet = calloc(1, sizeof(stylesheet_t));
	struct parser_state state = { 0 };
	while (*source) {
		uint32_t ch = utf8_decode(&source);
		stylesheet_parsec(stylesheet, &state, ch);
	}
	return stylesheet;
}
