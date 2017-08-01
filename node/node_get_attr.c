#include "util/hashtable.h"
#include "node.h"

const char *node_get_attr(struct sui_node *node, const char *key) {
	return (const char *)hashtable_get(node->attributes, key);
}
