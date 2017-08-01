#include <stdlib.h>
#include "css.h"

void selector_free(struct selector *selector) {
	while (selector) {
		free(selector->value);
		free(selector->attr_value);
		struct selector *next = selector->next;
		free(selector);
		selector = next;
	}
}
