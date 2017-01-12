#include <stdlib.h>
#include "node.h"
#include "util/hash.h"
#include "util/hashtable.h"
#include "util/list.h"
#include "util/set.h"

sui_node_t *sui_node_create() {
	sui_node_t *node = calloc(sizeof(sui_node_t), 1);
	if (!node) {
		return node;
	}

	// Note: it may be better later to only allocate these if they're assigned?
	node->classes = set_create(16, hash);
	node->children = list_create();
	node->attributes = hashtable_create(128, hash);

	return node;
}
