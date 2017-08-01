#define _XOPEN_SOURCE 500
#include <stdlib.h>
#include <string.h>
#include "util/hashtable.h"
#include "node.h"

void node_set_attr(struct sui_node *node, const char *key, const char *value) {
	if (node->impl && node->impl->attr) {
		if (!node->impl->attr(node, key, value)) {
			return;
		}
	}
	free(hashtable_set(node->attributes, key, strdup(value)));
}
