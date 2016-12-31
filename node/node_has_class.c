#include <stdbool.h>
#include "util/set.h"
#include "node.h"

bool node_has_class(sui_node_t *node, const char *name) {
	return set_contains(node->classes, name);
}
