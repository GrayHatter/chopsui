#include <stdlib.h>
#include <stdint.h>
#include "util/string.h"
#include "util/unicode.h"

static void sanity_check(str_t *str) {
	if (str->str == NULL) {
		str->str = malloc(16);
		str->size = 16;
		str->len = 0;
		str->str[0] = '\0';
	}
}

static void ensure_capacity(str_t *str, size_t len) {
	if (len + 1 >= str->size) {
		char *new = realloc(str->str, str->size * 2);
		str->str = new;
		str->size *= 2;
	}
}

str_t *str_create() {
	return calloc(sizeof(str_t), 1);
}

void str_free(str_t *str) {
	if (!str) return;
	free(str->str);
	free(str);
}

void str_append_ch(str_t *str, uint32_t ch) {
	int size = utf8_chsize(ch);
	if (size <= 0) {
		return;
	}
	sanity_check(str);
	ensure_capacity(str, str->len + size);
	utf8_encode(&str->str[str->len], ch);
	str->len += size;
	str->str[str->len] = '\0';
}
