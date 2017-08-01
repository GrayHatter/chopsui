#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "util/unicode.h"
#include "css.h"

static bool parse_selector_atom(struct selector *current, const char **src) {
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

struct selector *selector_parse(const char *src) {
	if (!*src) {
		return NULL;
	}
	struct selector *current = calloc(sizeof(struct selector), 1);
	struct selector *root = current;
	struct selector *prev = NULL;
	while (*src) {
		uint32_t ch = utf8_decode(&src);
		if (ch == UTF8_INVALID) {
			goto error;
		}
		if (isspace(ch)) {
			if (current != root) {
				current->type = SELECTOR_DESCENDANT;
				while (ch && isspace(ch)) {
					ch = utf8_decode(&src);
				}
				if (!ch) {
					break;
				}
				if (ch && !strchr(">~+", ch)) {
					current->next = calloc(sizeof(struct selector), 1);
					prev = current;
					current = current->next;
				}
			}
		}
		switch (ch) {
			case '>':
				current->type = SELECTOR_CHILD;
				do {
					ch = utf8_decode(&src);
				} while (isspace(ch));
				src -= utf8_chsize(ch);
				break;
			case '~':
				current->type = SELECTOR_SIBLING;
				do {
					ch = utf8_decode(&src);
				} while (isspace(ch));
				src -= utf8_chsize(ch);
				break;
			case '+':
				current->type = SELECTOR_NEXT_SIBLING;
				do {
					ch = utf8_decode(&src);
				} while (isspace(ch));
				src -= utf8_chsize(ch);
				break;
			case '[': // TODO: attribute selectors
				while (*src && *src != ']') ++src;
				if (*src) ++src;
				continue;
			case '*':
				current->type = SELECTOR_ANY;
				break;
			case '#':
				current->type = SELECTOR_ID;
				current->specificity += 0;
				if (!parse_selector_atom(current, &src)) {
					goto error;
				}
				break;
			case '.':
				current->type = SELECTOR_CLASS;
				current->specificity += 1;
				if (!parse_selector_atom(current, &src)) {
					goto error;
				}
				break;
			default:
				src -= utf8_chsize(ch);
				current->type = SELECTOR_TYPE;
				current->specificity += 2;
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
		selector_free(current);
		prev->next = NULL;
	}
	return root;
error:
	selector_free(root);
	return NULL;
}
