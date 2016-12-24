#include <stdlib.h>
#include "util/list.h"
#include "css.h"

static void style_property_free_iter(void *_prop, void *_) {
	struct style_property *prop = _prop;
	if (!prop) return;
	free(prop->name);
	free(prop->value);
	free(prop);
}

void style_rule_free(style_rule_t *rule) {
	if (!rule) return;
	for (size_t i = 0; rule->selectors && i < rule->selectors->length; ++i) {
		selector_t *s = rule->selectors->items[i];
		selector_free(s);
	}
	list_free(rule->selectors);
	if (rule->properties) {
		hashtable_iter(rule->properties, style_property_free_iter, NULL);
		hashtable_free(rule->properties);
	}
}
