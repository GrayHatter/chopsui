#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "util/unicode.h"
#include "css.h"

void selector_destroy(selector_t selector) {
	while (selector) {
		free(selector->value);
		free(selector->attr_value);
		selector_t next = selector->next;
		free(selector);
		selector = next;
	}
}

static bool parse_selector_atom(selector_t current, const char **src) {
	if (!*src) {
		return false;
	}
	char *atom = malloc(16);
	size_t len = 0, size = 16;
	while (*src) {
		uint32_t ch = utf8_decode(src);
		if (ch == UTF8_INVALID) {
			break;
		}
		switch (ch) {
			default:
				if (!isspace(ch)) {
					if (size - len > UTF8_MAX_SIZE + 1) {
						size *= 2;
						char *new = realloc(atom, size);
						if (!new) {
							free(atom);
							return false;
						}
						atom = new;
					}
					len += utf8_encode(atom + len, ch);
					break;
				}
				/* fallthrough */
			case '#':
			case '.':
			case '[':
			case '>':
			case '~':
			case '+':
				current->value = atom;
				src -= utf8_chsize(ch);
				return true;
		}
	}
	free(atom);
	return false;
}

selector_t parse_selector(const char *src) {
	if (!*src) {
		return NULL;
	}
	selector_t current = calloc(sizeof(struct selector), 1);
	selector_t root = current;
	while (*src) {
		uint32_t ch = utf8_decode(&src);
		if (ch == UTF8_INVALID) {
			goto error;
		}
		if (isspace(ch)) {
			continue;
		}
		switch (ch) {
			case '>':
				current->type = SELECTOR_CHILD;
				break;
			case '~':
				current->type = SELECTOR_SIBLING;
				break;
			case '+':
				current->type = SELECTOR_NEXT_SIBLING;
				break;
			case '[': // TODO: attribute selectors
				while (*src && *src != ']') ++src;
				if (*src) ++src;
				continue;
			case '#':
				++src;
				current->type = SELECTOR_ID;
				if (!parse_selector_atom(current, &src)) {
					goto error;
				}
				break;
			case '.':
				++src;
				current->type = SELECTOR_ID;
				if (!parse_selector_atom(current, &src)) {
					goto error;
				}
				break;
			default:
				current->type = SELECTOR_TYPE;
				if (!parse_selector_atom(current, &src)) {
					goto error;
				}
				break;
		}
		current->next = calloc(sizeof(struct selector), 1);
		current = current->next;
	}
	return root;
error:
	selector_destroy(root);
	return NULL;
}
