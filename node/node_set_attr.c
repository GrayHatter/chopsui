#define _XOPEN_SOURCE 500
#include <stdlib.h>
#include <string.h>
#include "util/hashtable.h"
#include "node.h"

void node_set_attr(sui_node_t *node, const char *key, const char *value) {
	if (node->impl && node->impl->attr) {
		node->impl->attr(node, key, value);
	} else {
		//char *val = strdup(value);
		/*char *prev = */free(hashtable_set(node->attributes, key, strdup(value)));
		// TODO: node_raise_event("attr", node, attr_event_create(name, val, prev));
	}
}
