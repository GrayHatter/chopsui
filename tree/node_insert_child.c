#include "util/list.h"
#include "node.h"
#include "tree.h"

int node_insert_child(sui_node_t *parent, sui_node_t *child, size_t index) {
	if (!child || !parent || child->parent != NULL || index > parent->children->length) {
		return 0;
	}
	list_insert(parent->children, index, child);
	child->parent = parent;
	return 1;
}
