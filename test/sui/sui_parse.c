#include <string.h>
#include <assert.h>
#include "test.h"
#include "sui.h"

char *test_name = "sui/sui_parse";

static int test_type() {
	sui_node_t *node = sui_parse("test", NULL);
	assert(node && strcmp(node->type, "test") == 0);
	return 0;
}

int test_main() {
	return test_type()
	;
}
