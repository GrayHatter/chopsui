#include "util/hashtable.h"
#include "util/hash.h"
#include "type.h"

hashtable_t *types = NULL;

struct sui_type_impl *get_impl_for_type(const char *type) {
	if (!types) {
		return NULL;
	}
	return (struct sui_type_impl *)hashtable_get(types, type);
}

void set_impl_for_type(const char *type, struct sui_type_impl *impl) {
	if (!types) {
		types = hashtable_create(256, hash);
	}
	hashtable_set(types, type, impl);
}
