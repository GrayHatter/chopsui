#include <string.h>
#include <assert.h>
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
	selector = rule->selectors->items[1];
	assert(selector && selector->type == SELECTOR_TYPE);

	stylesheet_free(ss);
	return 0;

}

int test_main() {
	return test_comments()
		|| test_selector()
		|| test_multiple_rules()
		|| test_multiple_selectors()
	;
}
