#ifndef _SUI_NODE_H
#define _SUI_NODE_H

#include <stdbool.h>
//#include "Yoga.h"
//#include "util/bloom.h"
#include "util/hashtable.h"
#include "util/list.h"
#include "util/set.h"
#include "type.h"

struct sui_node {
//	YGNodeRef layout_node;
	struct sui_node *parent;

	char *id;
	set_t *classes;          // char *
	list_t *children;        // sui_node_t
	hashtable_t *attributes; // char *, char *

	void *impl_state;
	sui_type_impl_t impl;

//	bloom_t ancestors;
};

typedef struct sui_node sui_node_t;

/**
 * Returns the value of the specified attribute.
 */
const char *node_get_attr(sui_node_t *node, const char *key);
/**
 * Sets the specified attribute to the specified value.
 */
void node_set_attr(sui_node_t *node, const char *key, const char *value);

/**
 * Checks if the specified node has the specified class.
 */
bool node_has_class(sui_node_t *node, const char *name);
/**
 * Adds the specified class to the specified node.
 */
void node_add_class(sui_node_t *node, const char *name);
/**
 * Removes the specified class to the specified node.
 */
void node_remove_class(sui_node_t *node, const char *name);

/**
 * Frees this node and all of its children. Detaches it from the parent first if
 * necessary.
 */
void node_free(sui_node_t *node);

#endif
