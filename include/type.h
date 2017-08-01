#ifndef _SUI_TYPE_H
#define _SUI_TYPE_H
#include <stdint.h>

struct sui_node;

struct sui_type_impl {
	/**
	 * Invoked when a new node is created of this type.
	 */
	void (*init)(struct sui_node *node);
	/**
	 * Invoked when this node is destroyed.
	 */
	void (*free)(struct sui_node *node);
	/**
	 * Invoked when an attribute is set on this node. Return false to prevent
	 * the change from being applied.
	 */
	bool (*attr)(struct sui_node *node, const char *key, const char *value);
	/**
	 * Return the valid scalar types for this attribute, ORed together.
	 */
	uint64_t (*attr_spec)(struct sui_node *node, const char *key);
	/**
	 * Return the default value for this attribute, or NULL. We take ownership
	 * over the value you give us, we'll free it.
	 */
	struct sui_scalar *(*attr_default)(const char *key);
	/**
	 * Invoked when a child is added to this node. Return false to prevent the
	 * child from being added and raise an error.
	 */
	bool (*child)(struct sui_node *node, struct sui_node *child);
	/**
	 * Invoked when a child is removed from this node.
	 */
	void (*child_removed)(struct sui_node *node, struct sui_node *child);
};

struct sui_type_impl *get_impl_for_type(const char *type);
void set_impl_for_type(const char *type, struct sui_type_impl *impl);

#endif
