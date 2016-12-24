#include <stdlib.h>
#include "util/list.h"
#include "css.h"

void stylesheet_free(stylesheet_t *css) {
	if (!css) return;
	for (size_t i = 0; i < css->rules->length; ++i) {
		style_rule_t *rule = css->rules->items[i];
		style_rule_free(rule);
	}
	list_free(css->rules);
	for (size_t i = 0; i < css->media_rules->length; ++i) {
		media_rule_t *rule = css->media_rules->items[i];
		media_rule_free(rule);
	}
	list_free(css->media_rules);
	for (size_t i = 0; i < css->keyframes->length; ++i) {
		keyframes_t *keyframes = css->keyframes->items[i];
		keyframes_free(keyframes);
	}
	list_free(css->keyframes);
	free(css);
}
