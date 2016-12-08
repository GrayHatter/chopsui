#ifndef _SUI_TREE_H
#define _SUI_TREE_H

#include "Yoga.h"
#include "bloom.h"
#include "hashtable.h"
#include "list.h"
#include "set.h"
#include "elements.h"
#include "css.h"

struct sui_node {
	YGNodeRef layout_node;
	struct sui_node *parent;

	char *id;
	set_t classes;				// char *
	list_t children;			// sui_node_t
	hashtable_t attributes; 	// char *, char *

	void *impl_state;
	sui_elem_impl_t elem_impl;

	bloom_t ancestors;
};

typedef struct sui_node *sui_node_t;

/**
 * Finds the first ancestor of node that matches the provided CSS selector.
 */
sui_node_t sui_find_ancestor(sui_node_t node, const char *selector);
/**
 * Creates and returns a list_t of references to ancestors of node that match
 * the provided CSS selector.
 */
list_t *sui_find_ancestors(sui_node_t node, const char *selector);
/**
 * Invokes the provided iter function with each anscestor of the node that
 * matches the provided CSS selector.
 */
void sui_iter_ancestors(sui_node_t node, const char *selector, void (*iter)(sui_node_t node));

/**
 * Finds the first descendant of node that matches the provided CSS selector.
 */
sui_node_t sui_find_descendant(sui_node_t node, const char *selector);
/**
 * Creates and returns a list_t of references to descendants of node that
 * match the provided CSS selector.
 */
list_t *sui_find_descendants(sui_node_t node, const char *selector);
/**
 * Invokes the provided iter function with each descendant of node that matches the
 * provided CSS selector.
 */
void sui_iter_descendants(sui_node_t node, const char *selector, void (*iter)(sui_node_t node));

/**
 * Adds the node to the end of the parent's children.
 */
void sui_add_child(sui_node_t parent, sui_node_t child);
/**
 * Inserts the node in the parent's children at the specified index.
 */
void sui_insert_child(sui_node_t parent, sui_node_t child, int index);

/**
 * Detaches this node from its parent.
 */
void sui_detach(sui_node_t child);

/**
 * Frees this node and all of its children. Detaches it from the parent first if
 * necessary.
 */
void sui_free_node(sui_node_t node);

#endif
