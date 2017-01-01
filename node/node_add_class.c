#include <stdbool.h>
#include "util/set.h"
#include "node.h"

void node_add_class(sui_node_t *node, const char *name) {
	set_add(node->classes, name);
}
