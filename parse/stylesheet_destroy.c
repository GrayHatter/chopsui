#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "util/list.h"
#include "css.h"

static void style_property_free_iter(void *_prop, void *_) {
	struct style_property *prop = _prop;
	if (!prop) return;
	free(prop->name);
	free(prop->value);
	free(prop);
}

static void style_rule_destroy(style_rule_t *rule) {
	if (!rule) return;
	for (size_t i = 0; rule->selectors && i < rule->selectors->length; ++i) {
		selector_t *s = rule->selectors->items[i];
		selector_destroy(s);
	}
	list_destroy(rule->selectors);
	if (rule->properties) {
		hashtable_iter(rule->properties, style_property_free_iter, NULL);
		hashtable_destroy(rule->properties);
	}
}

static void media_rule_destroy(media_rule_t *rule) {
	while (rule) {
		media_rule_t *next = rule->next;
		free(rule);
		rule = next;
	}
}

static void keyframe_destroy(struct keyframe *key) {
	if (!key) return;
	for (size_t i = 0; key->rules && key->rules->length; ++i) {
		style_rule_t *rule = key->rules->items[i];
		style_rule_destroy(rule);
	}
	list_destroy(key->rules);
	free(key);
}

static void keyframes_destroy(keyframes_t *keyframes) {
	if (!keyframes) return;
	for (size_t i = 0; keyframes->keys && i < keyframes->keys->length; ++i) {
		struct keyframe *key = keyframes->keys->items[i];
		keyframe_destroy(key);
	}
	list_destroy(keyframes->keys);
	free(keyframes->identifier);
	free(keyframes);
}

void stylesheet_destroy(stylesheet_t *css) {
	if (!css) return;
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
