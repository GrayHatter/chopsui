#include <stdlib.h>
#include "util/list.h"
#include "css.h"

static void keyframe_free(struct keyframe *key) {
	if (!key) return;
	for (size_t i = 0; key->rules && key->rules->length; ++i) {
		struct style_rule *rule = key->rules->items[i];
		style_rule_free(rule);
	}
	list_free(key->rules);
	free(key);
}

void keyframes_free(struct keyframes *keyframes) {
	if (!keyframes) return;
	for (size_t i = 0; keyframes->keys && i < keyframes->keys->length; ++i) {
		struct keyframe *key = keyframes->keys->items[i];
		keyframe_free(key);
	}
	list_free(keyframes->keys);
	free(keyframes->identifier);
	free(keyframes);
}
