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
	if (!*src || !**src) {
		return false;
	}
	char *atom = malloc(16);
	size_t len = 0, size = 16;
	while (**src) {
		uint32_t ch = utf8_decode(src);
		if (ch == UTF8_INVALID) {
			free(atom);
			return false;
		}
		switch (ch) {
			default:
				if (!isspace(ch)) {
					if (size - len < UTF8_MAX_SIZE + 1) {
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
				*src -= utf8_chsize(ch);
				goto finish;
		}
	}
finish:
	atom[len] = '\0';
	current->value = atom;
	return true;
}

selector_t selector_parse(const char *src) {
	if (!*src) {
		return NULL;
	}
	selector_t current = calloc(sizeof(struct selector), 1);
	selector_t root = current;
	selector_t prev = NULL;
	while (*src) {
		uint32_t ch = utf8_decode(&src);
		if (ch == UTF8_INVALID) {
			goto error;
		}
		if (isspace(ch)) {
			if (current != root) {
				current->type = SELECTOR_DESCENDANT;
				while (isspace(ch)) {
					ch = utf8_decode(&src);
				}
				if (*src) {
					current->next = calloc(sizeof(struct selector), 1);
					prev = current;
					current = current->next;
				}
			}
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
				current->type = SELECTOR_ID;
				if (!parse_selector_atom(current, &src)) {
					goto error;
				}
				break;
			case '.':
				current->type = SELECTOR_CLASS;
				if (!parse_selector_atom(current, &src)) {
					goto error;
				}
				break;
			default:
				src -= utf8_chsize(ch);
				current->type = SELECTOR_TYPE;
				if (!parse_selector_atom(current, &src)) {
					goto error;
				}
				break;
		}
		if (*src) {
			current->next = calloc(sizeof(struct selector), 1);
			prev = current;
			current = current->next;
		}
	}
	if (current->type == SELECTOR_DESCENDANT) {
		selector_destroy(current);
		current = prev;
	}
	return root;
error:
	selector_destroy(root);
	return NULL;
}
