#ifndef _SUI_TREE_H
#define _SUI_TREE_H

#include "util/list.h"
#include "node.h"
#include "type.h"
#include "css.h"

/**
 * Finds the first ancestor of node that matches the provided CSS selector.
 */
struct sui_node node_find_ancestor(struct sui_node *node, struct selector *selector);
/**
 * Creates and returns a list_t of references to ancestors of node that match
 * the provided CSS selector.
 */
list_t *node_find_ancestors(struct sui_node *node, struct selector *selector);
/**
 * Invokes the provided iter function with each anscestor of the node that
 * matches the provided CSS selector.
 */
void node_iter_ancestors(struct sui_node *node, struct selector *selector,
		void (*iter)(struct sui_node *node));

/**
 * Finds the first descendant of node that matches the provided CSS selector.
 */
struct sui_node node_find_descendant(struct sui_node *node, struct selector *selector);
/**
 * Creates and returns a list_t of references to descendants of node that
 * match the provided CSS selector.
 */
list_t *node_find_descendants(struct sui_node *node, struct selector *selector);
/**
 * Invokes the provided iter function with each descendant of node that matches the
 * provided CSS selector.
 */
void node_iter_descendants(struct sui_node *node, struct selector *selector,
		void (*iter)(struct sui_node *node));

/**
 * Adds the node to the end of the parent's children. Returns the number of
 * nodes inserted - could be 0 if the child already has a parent, or is NULL.
 */
int node_append_child(struct sui_node *parent, struct sui_node *child);
/**
 * Inserts the node in the parent's children at the specified index. Returns the
 * number of nodes inserted - could be 0 if the child already has a parent, or
 * is NULL.
 */
int node_insert_child(struct sui_node *parent, struct sui_node *child, size_t index);

/**
 * Detaches this node from its parent.
 */
void node_detach(struct sui_node *child);

#endif
