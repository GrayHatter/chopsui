#include "util/hashtable.h"
#include "util/hash.h"
#include "type.h"

hashtable_t *types = NULL;

sui_type_impl_t *get_impl_for_type(const char *type) {
	if (!types) {
		return NULL;
	}
	return (sui_type_impl_t *)hashtable_get(types, type);
}

void set_impl_for_type(const char *type, sui_type_impl_t *impl) {
	if (!types) {
		types = hashtable_create(256, hash);
	}
	hashtable_set(types, type, impl);
}
