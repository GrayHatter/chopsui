#include <string.h>
#include <assert.h>
#include "util/hashtable.h"
#include "test.h"
#include "css.h"

char *test_name = "parse/css_parse";

static int test_comments() {
	stylesheet_t *ss = css_parse("/* this should cause\n"
			"a syntax error if comments aren't being handled\n"
			"correctly. */");
	stylesheet_free(ss);
	return 0;
}

static int test_selector() {
	stylesheet_t *ss = css_parse("foo .bar { }");
	assert(ss->rules->length == 1);
	style_rule_t *rule = ss->rules->items[0];
	assert(rule && rule->selectors->length == 1);
	selector_t *selector = rule->selectors->items[0];
	assert(selector && selector->type == SELECTOR_TYPE);
	selector = selector->next;
	assert(selector && selector->type == SELECTOR_DESCENDANT);
	selector = selector->next;
	assert(selector && selector->type == SELECTOR_CLASS);
	assert(!selector->next);
	stylesheet_free(ss);
	return 0;
}

static int test_multiple_rules() {
	stylesheet_t *ss = css_parse("foo { } bar { }");
	assert(ss->rules->length == 2);

	style_rule_t *rule = ss->rules->items[0];
	assert(rule && rule->selectors->length == 1);
	selector_t *selector = rule->selectors->items[0];
	assert(selector && selector->type == SELECTOR_TYPE);

	rule = ss->rules->items[1];
	assert(rule && rule->selectors->length == 1);
	selector = rule->selectors->items[0];
	assert(selector && selector->type == SELECTOR_TYPE);

	stylesheet_free(ss);
	return 0;
}

static int test_multiple_selectors() {
	stylesheet_t *ss = css_parse("foo, bar { }");
	assert(ss->rules->length == 1);

	style_rule_t *rule = ss->rules->items[0];
	assert(rule && rule->selectors->length == 2);
	selector_t *selector = rule->selectors->items[0];
	assert(selector && selector->type == SELECTOR_TYPE);
	assert(strcmp(selector->value, "foo") == 0);
	assert(!selector->next);

	selector = rule->selectors->items[1];
	assert(selector && selector->type == SELECTOR_TYPE);
	assert(strcmp(selector->value, "bar") == 0);
	assert(!selector->next);

	stylesheet_free(ss);
	return 0;
}

static int test_properties() {
	stylesheet_t *ss = css_parse("foo { background: red; }");
	assert(ss->rules->length == 1);

	style_rule_t *rule = ss->rules->items[0];
	assert(rule);

	char *value = hashtable_get(rule->properties, "background");
	assert(value && strcmp(value, "red") == 0);

	stylesheet_free(ss);
	return 0;
}

static int test_multi_properties() {
	stylesheet_t *ss = css_parse("foo { \n"
			"\tbackground: red;\n"
			"\tfont-weight: bold;\n"
			"}");
	assert(ss->rules->length == 1);

	style_rule_t *rule = ss->rules->items[0];
	assert(rule);

	char *value = hashtable_get(rule->properties, "background");
	assert(value && strcmp(value, "red") == 0);

	value = hashtable_get(rule->properties, "font-weight");
	assert(value && strcmp(value, "bold") == 0);

	stylesheet_free(ss);
	return 0;
}

static int test_quoted_properties() {
	stylesheet_t *ss = css_parse("foo { \n"
			"\ttext: \"hello: {world};!\";\n"
			"\theader: 'hello: \\'world\\';!';\n"
			"}");
	assert(ss->rules->length == 1);

	style_rule_t *rule = ss->rules->items[0];
	assert(rule);

	char *value = hashtable_get(rule->properties, "text");
	assert(value && strcmp(value, "hello: {world};!") == 0);

	value = hashtable_get(rule->properties, "header");
	assert(value && strcmp(value, "hello: \'world\';!") == 0);

	stylesheet_free(ss);
	return 0;
}

int test_main() {
	return test_comments()
		|| test_selector()
		|| test_multiple_rules()
		|| test_multiple_selectors()
		|| test_properties()
		|| test_multi_properties()
		|| test_quoted_properties()
	;
}
