#ifndef _SUI_TREE_H
#define _SUI_TREE_H

#include "util/list.h"
#include "node.h"
#include "elements.h"
#include "css.h"

/**
 * Finds the first ancestor of node that matches the provided CSS selector.
 */
sui_node_t node_find_ancestor(sui_node_t node, const char *selector);
/**
 * Creates and returns a list_t of references to ancestors of node that match
 * the provided CSS selector.
 */
list_t *node_find_ancestors(sui_node_t node, const char *selector);
/**
 * Invokes the provided iter function with each anscestor of the node that
 * matches the provided CSS selector.
 */
void node_iter_ancestors(sui_node_t node, const char *selector, void (*iter)(sui_node_t node));

/**
 * Finds the first descendant of node that matches the provided CSS selector.
 */
sui_node_t node_find_descendant(sui_node_t node, const char *selector);
/**
 * Creates and returns a list_t of references to descendants of node that
 * match the provided CSS selector.
 */
list_t *node_find_descendants(sui_node_t node, const char *selector);
/**
 * Invokes the provided iter function with each descendant of node that matches the
 * provided CSS selector.
 */
void node_iter_descendants(sui_node_t node, const char *selector, void (*iter)(sui_node_t node));

/**
 * Adds the node to the end of the parent's children.
 */
void node_add_child(sui_node_t parent, sui_node_t child);
/**
 * Inserts the node in the parent's children at the specified index.
 */
void node_insert_child(sui_node_t parent, sui_node_t child, int index);

/**
 * Detaches this node from its parent.
 */
void node_detach(sui_node_t child);

#endif
