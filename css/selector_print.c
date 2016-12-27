#include <stdbool.h>
#include "util/unicode.h"
#include "css.h"

static void sputs(void (*putch)(uint32_t ch), const char *s) {
	while (*s) {
		uint32_t ch = utf8_decode(&s);
		putch(ch);
	}
}

void selector_print(selector_t *s, bool pretty,
		void (*putch)(uint32_t ch)) {
	while (s) {
		switch (s->type) {
		case SELECTOR_TYPE:
			sputs(putch, s->value);
			break;
		case SELECTOR_ID:
			putch('#');
			sputs(putch, s->value);
			break;
		case SELECTOR_CLASS:
			putch('.');
			sputs(putch, s->value);
			break;
		case SELECTOR_ATTRIBUTE:
			putch('[');
			sputs(putch, s->value);
			/* TODO:
			switch (s->comparison) {
			}
			*/
			putch(']');
			break;
		case SELECTOR_DESCENDANT:
			putch(' ');
			break;
		case SELECTOR_CHILD:
			if (pretty) {
				sputs(putch, " > ");
			} else {
				putch('>');
			}
			break;
		case SELECTOR_SIBLING:
			if (pretty) {
				sputs(putch, " ~ ");
			} else {
				putch('~');
			}
			break;
		case SELECTOR_NEXT_SIBLING:
			if (pretty) {
				sputs(putch, " + ");
			} else {
				putch('+');
			}
			break;
		}
		s = s->next;
	}
}
