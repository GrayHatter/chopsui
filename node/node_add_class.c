#include <stdbool.h>
#include "util/set.h"
#include "node.h"

void node_add_class(struct sui_node *node, const char *name) {
	set_add(node->classes, name);
}
