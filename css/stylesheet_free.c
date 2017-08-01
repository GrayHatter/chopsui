#include <stdlib.h>
#include "util/list.h"
#include "css.h"

void stylesheet_free(struct stylesheet *css) {
	if (!css) return;
	for (size_t i = 0; i < css->rules->length; ++i) {
		struct style_rule *rule = css->rules->items[i];
		style_rule_free(rule);
	}
	list_free(css->rules);
	for (size_t i = 0; i < css->media_rules->length; ++i) {
		struct media_rule *rule = css->media_rules->items[i];
		media_rule_free(rule);
	}
	list_free(css->media_rules);
	for (size_t i = 0; i < css->keyframes->length; ++i) {
		struct keyframes *keyframes = css->keyframes->items[i];
		keyframes_free(keyframes);
	}
	list_free(css->keyframes);
	free(css);
}
