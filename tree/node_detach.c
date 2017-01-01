#include "util/list.h"
#include "node.h"
#include "tree.h"

void node_detach(sui_node_t *node) {
	if (!node || !node->parent) {
		return;
	}
	for (size_t i = 0; i < node->parent->children->length; ++i) {
		sui_node_t *n = node->parent->children->items[i];
		if (n == node) {
			list_del(node->parent->children, i);
			node->parent = NULL;
			return;
		}
	}
}
