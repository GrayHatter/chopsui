#ifndef _SUI_TYPE_H
#define _SUI_TYPE_H

typedef struct sui_node sui_node_t;

struct sui_type_impl {
	void (*free)(sui_node_t *node);
	void (*attr)(sui_node_t *node, const char *key, const char *value);
};

typedef struct sui_type_impl *sui_type_impl_t;

sui_type_impl_t *get_impl_for_type(const char *type);
void set_impl_for_type(const char *type, sui_type_impl_t *impl);

#endif
