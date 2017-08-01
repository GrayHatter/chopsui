#ifndef _SUI_NODE_H
#define _SUI_NODE_H

#include <stdbool.h>
#include "util/hashtable.h"
#include "util/list.h"
#include "util/set.h"
#include "type.h"

struct sui_node {
	struct sui_node *parent;

	char *type;
	char *id;
	set_t *classes;          // char *
	list_t *children;        // struct sui_node
	hashtable_t *attributes; // char *, char *

	void *impl_state;
	struct sui_type_impl *impl;
};

/**
 * Returns the value of the specified attribute.
 */
const char *node_get_attr(struct sui_node *node, const char *key);
/**
 * Sets the specified attribute to the specified value.
 */
void node_set_attr(struct sui_node *node, const char *key, const char *value);

/**
 * Checks if the specified node has the specified class.
 */
bool node_has_class(struct sui_node *node, const char *name);
/**
 * Adds the specified class to the specified node.
 */
void node_add_class(struct sui_node *node, const char *name);
/**
 * Removes the specified class to the specified node.
 */
void node_remove_class(struct sui_node *node, const char *name);

/**
 * Frees this node and all of its children. Detaches it from the parent first if
 * necessary.
 */
void node_free(struct sui_node *node);

#endif
