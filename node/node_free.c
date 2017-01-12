#include <stdlib.h>
#include "node.h"
#include "tree.h"

static void free_attr_iter(void *val, void *_) {
	free(val);
}

void node_free(sui_node_t *node) {
	node_detach(node);
	free(node->id);
	set_free(node->classes);
	for (size_t i = 0; node->children && i < node->children->length; ++i) {
		node_free((sui_node_t *)node->children->items[i]);
	}
	list_free(node->children);
	if (node->attributes) {
		hashtable_iter(node->attributes, free_attr_iter, NULL);
		hashtable_free(node->attributes);
	}
	if (node->impl && node->impl->free) {
		node->impl->free(node);
	}
}
