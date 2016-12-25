#include <string.h>
#include <assert.h>
#include "test.h"
#include "css.h"

char *test_name = "parse/selector_parse";

static int test_basic_type() {
	selector_t *selector = selector_parse("test");
	assert(selector->type == SELECTOR_TYPE);
	assert(strcmp(selector->value, "test") == 0);
	assert(!selector->next);
	selector_free(selector);
	return 0;
}

static int test_trailing_space() {
	selector_t *selector = selector_parse("test ");
	assert(selector->type == SELECTOR_TYPE);
	assert(strcmp(selector->value, "test") == 0);
	assert(!selector->next);
	selector_free(selector);
	return 0;
}

static int test_basic_class() {
	selector_t *selector = selector_parse(".test");
	assert(selector->type == SELECTOR_CLASS);
	assert(strcmp(selector->value, "test") == 0);
	assert(!selector->next);
	selector_free(selector);
	return 0;
}

static int test_basic_id() {
	selector_t *selector = selector_parse("#test");
	assert(selector->type == SELECTOR_ID);
	assert(strcmp(selector->value, "test") == 0);
	assert(!selector->next);
	selector_free(selector);
	return 0;
}

static int test_descendants() {
	selector_t *selector = selector_parse("foo .bar #baz");
	assert(selector->type == SELECTOR_TYPE);
	assert(strcmp(selector->value, "foo") == 0);
	assert(selector->next);
	assert(selector->next->type == SELECTOR_DESCENDANT);
	assert(selector->next->next);
	assert(selector->next->next->type == SELECTOR_CLASS);
	assert(strcmp(selector->next->next->value, "bar") == 0);
	assert(selector->next->next->next);
	assert(selector->next->next->next->type == SELECTOR_DESCENDANT);
	assert(selector->next->next->next->next);
	assert(selector->next->next->next->next->type == SELECTOR_ID);
	assert(strcmp(selector->next->next->next->next->value, "baz") == 0);
	selector_free(selector);
	return 0;
}

static int test_pairs() {
	selector_t *selector = selector_parse("foo.bar");
	assert(selector->type == SELECTOR_TYPE);
	assert(strcmp(selector->value, "foo") == 0);
	assert(selector->next);
	assert(selector->next->type == SELECTOR_CLASS);
	assert(strcmp(selector->next->value, "bar") == 0);
	selector_free(selector);
	return 0;
}

static int test_child() {
	selector_t *selector = selector_parse("foo > .bar");
	assert(selector->type == SELECTOR_TYPE);
	assert(strcmp(selector->value, "foo") == 0);
	assert(selector->next);
	assert(selector->next->type == SELECTOR_CHILD);
	assert(selector->next->next);
	assert(selector->next->next->type == SELECTOR_CLASS);
	assert(strcmp(selector->next->next->value, "bar") == 0);
	assert(!selector->next->next->next);
	selector_free(selector);
	return 0;
}

static int test_sibling() {
	selector_t *selector = selector_parse("foo ~ .bar");
	assert(selector->type == SELECTOR_TYPE);
	assert(strcmp(selector->value, "foo") == 0);
	assert(selector->next);
	assert(selector->next->type == SELECTOR_SIBLING);
	assert(selector->next->next);
	assert(selector->next->next->type == SELECTOR_CLASS);
	assert(strcmp(selector->next->next->value, "bar") == 0);
	assert(!selector->next->next->next);
	selector_free(selector);
	return 0;
}

static int test_next_sibling() {
	selector_t *selector = selector_parse("foo + .bar");
	assert(selector->type == SELECTOR_TYPE);
	assert(strcmp(selector->value, "foo") == 0);
	assert(selector->next);
	assert(selector->next->type == SELECTOR_NEXT_SIBLING);
	assert(selector->next->next);
	assert(selector->next->next->type == SELECTOR_CLASS);
	assert(strcmp(selector->next->next->value, "bar") == 0);
	assert(!selector->next->next->next);
	selector_free(selector);
	return 0;
}

int test_main() {
	return test_basic_type()
		|| test_trailing_space()
		|| test_basic_class()
		|| test_basic_id()
		|| test_descendants()
		|| test_pairs()
		|| test_child()
		|| test_sibling()
		|| test_next_sibling()
	;
}
