#ifndef _SUI_ELEMENTS_H
#define _SUI_ELEMENTS_H

#include "node.h"

struct sui_elem_impl {
	void (*free)(sui_node_t node);
	void (*attr)(sui_node_t node, const char *key, const char *value);
};

typedef struct sui_elem_impl *sui_elem_impl_t;
