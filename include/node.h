#ifndef _SUI_NODE_H
#define _SUI_NODE_H

#include <stdbool.h>
#include "Yoga.h"
#include "bloom.h"
#include "hashtable.h"
#include "list.h"
#include "set.h"

struct sui_node {
	YGNodeRef layout_node;
	struct sui_node *parent;

	char *id;
	set_t classes;          // char *
	list_t children;        // sui_node_t
	hashtable_t attributes; // char *, char *

	void *impl_state;
	sui_elem_impl_t elem_impl;

	bloom_t ancestors;
};

typedef struct sui_node *sui_node_t;

/**
 * Returns the value of the specified attribute.
 */
const char *sui_get_attr(sui_node_t node, const char *key);
/**
 * Sets the specified attribute to the specified value.
 */
void sui_set_attr(sui_node_t node, const char *key, const char *value);

/**
 * Checks if the specified node has the specified class.
 */
bool sui_has_class(sui_node_t node, const char *name);
/**
 * Adds the specified class to the specified node.
 */
void sui_add_class(sui_node_t node, const char *name);
/**
 * Removes the specified class to the specified node.
 */
void sui_remove_class(sui_node_t node, const char *name);

/**
 * Frees this node and all of its children. Detaches it from the parent first if
 * necessary.
 */
void sui_free_node(sui_node_t node);

#endif
