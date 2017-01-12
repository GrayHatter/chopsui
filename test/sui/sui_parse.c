#include <string.h>
#include <assert.h>
#include "test.h"
#include "node.h"
#include "sui.h"

char *test_name = "sui/sui_parse";

static int test_type() {
	sui_node_t *node = sui_parse("test", NULL);
	assert(node && strcmp(node->type, "test") == 0);
	node_free(node);
	return 0;
}

static int test_class() {
	sui_node_t *node = sui_parse("test .foo", NULL);
	assert(node && strcmp(node->type, "test") == 0);
	assert(node_has_class(node, "foo"));
	node_free(node);

	node = sui_parse("test .foo.bar .baz", NULL);
	assert(node && strcmp(node->type, "test") == 0);
	assert(node_has_class(node, "foo"));
	assert(node_has_class(node, "bar"));
	assert(node_has_class(node, "baz"));
	node_free(node);
	return 0;
}

static int test_id() {
	sui_node_t *node = sui_parse("test @foo", NULL);
	assert(node && strcmp(node->type, "test") == 0);
	assert(strcmp(node->id, "foo") == 0);
	node_free(node);
	return 0;
}

static int test_children() {
	sui_node_t *node = sui_parse(
			"test\n"
			"\tfoo\n"
			"\tbar\n"
			"\t\tbaz",
			NULL);
	assert(node && strcmp(node->type, "test") == 0);
	assert(node->children->length == 2);
	sui_node_t *n = node->children->items[0];
	assert(n && strcmp(n->type, "foo") == 0);
	n = node->children->items[1];
	assert(n && strcmp(n->type, "bar") == 0);
	assert(n->children->length == 1);
	node_free(node);
	return 0;
}

int test_main() {
	return test_type()
		|| test_class()
		|| test_id()
		|| test_children()
	;
}
