#include "util/hashtable.h"
#include "node.h"

const char *node_get_attr(sui_node_t *node, const char *key) {
	return (const char *)hashtable_get(node->attributes, key);
}
