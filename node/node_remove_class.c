#include <stdbool.h>
#include "util/set.h"
#include "node.h"

void node_remove_class(sui_node_t *node, const char *name) {
	set_del(node->classes, name);
}
