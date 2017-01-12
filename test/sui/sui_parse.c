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

int test_main() {
	return test_type()
		|| test_class()
		|| test_id()
	;
}
