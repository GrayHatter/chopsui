#include <stdlib.h>
#include "css.h"

void selector_free(selector_t *selector) {
	while (selector) {
		free(selector->value);
		free(selector->attr_value);
		selector_t *next = selector->next;
		free(selector);
		selector = next;
	}
}
