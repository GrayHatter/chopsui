#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "util/list.h"
#include "css.h"

static void style_rule_destroy(style_rule_t *rule) {
	for (size_t i = 0; i < rule->selectors->length; ++i) {
		selector_t *s = rule->selectors->items[i];
		selector_destroy(s);
	}
	list_destroy(rule->selectors);
}

static void media_rule_destroy(media_rule_t *rule) {
}

static void keyframes_destroy(keyframes_t *keyframes) {
}

void stylesheet_destroy(stylesheet_t *css) {
	if (!css) {
		return;
	}

	for (size_t i = 0; i < css->rules->length; ++i) {
		style_rule_t *rule = css->rules->items[i];
		style_rule_destroy(rule);
	}
	list_destroy(css->rules);

	for (size_t i = 0; i < css->media_rules->length; ++i) {
		media_rule_t *rule = css->media_rules->items[i];
		media_rule_destroy(rule);
	}
	list_destroy(css->media_rules);

	for (size_t i = 0; i < css->keyframes->length; ++i) {
		keyframes_t *keyframes = css->keyframes->items[i];
		keyframes_destroy(keyframes);
	}
	list_destroy(css->keyframes);

	free(css);
}
