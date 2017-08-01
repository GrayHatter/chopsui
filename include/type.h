#ifndef _SUI_TYPE_H
#define _SUI_TYPE_H
#include <stdint.h>

typedef struct sui_node sui_node_t;

struct sui_type_impl {
	/**
	 * Invoked when a new node is created of this type.
	 */
	void (*init)(sui_node_t *node);
	/**
	 * Invoked when this node is destroyed.
	 */
	void (*free)(sui_node_t *node);
	/**
	 * Invoked when an attribute is set on this node. Return false to prevent
	 * the change from being applied.
	 */
	bool (*attr)(sui_node_t *node, const char *key, const char *value);
	/**
	 * Return the valid scalar types for this attribute, ORed together.
	 */
	uint64_t (*attr_spec)(sui_node_t *node, const char *key);
	/**
	 * Invoked when a child is added to this node. Return false to prevent the
	 * child from being added and raise an error.
	 */
	bool (*child)(sui_node_t *node, sui_node_t *child);
	/**
	 * Invoked when a child is removed from this node.
	 */
	void (*child_removed)(sui_node_t *node, sui_node_t *child);
};

typedef struct sui_type_impl *sui_type_impl_t;

sui_type_impl_t *get_impl_for_type(const char *type);
void set_impl_for_type(const char *type, sui_type_impl_t *impl);

#endif
