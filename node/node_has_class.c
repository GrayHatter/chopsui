#include <stdbool.h>
#include "util/set.h"
#include "node.h"

bool node_has_class(struct sui_node *node, const char *name) {
	return set_contains(node->classes, name);
}
