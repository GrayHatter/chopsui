#include "util/list.h"
#include "node.h"
#include "tree.h"

int node_insert_child(struct sui_node *parent, struct sui_node *child,
		size_t index) {
	if (!child
			|| !parent
			|| child->parent != NULL
			|| index > parent->children->length) {
		return 0;
	}
	list_insert(parent->children, index, child);
	child->parent = parent;
	return 1;
}
