/*
 * util/set.c - implements a generic set
 */
#include <stdbool.h>
#include <stdlib.h>

#include "util/set.h"

set_t *set_create(size_t buckets, unsigned int (*hash_function)(const void *)) {
	set_t *set = malloc(sizeof(set_t));
	set->hash = hash_function;
	set->bucket_count = buckets;
	set->buckets = calloc(buckets, sizeof(set_entry_t));
	return set;
}

void free_bucket(set_entry_t *bucket) {
	if (bucket) {
		free_bucket(bucket->next);
		free(bucket);
	}
}

void set_destroy(set_t *set) {
	for (size_t i = 0; i < set->bucket_count; ++i) {
		free_bucket(set->buckets[i]);
	}
	free(set);
}

bool set_contains(set_t *set, const void *key) {
	unsigned int hash = set->hash(key);
	unsigned int bucket = hash % set->bucket_count;
	set_entry_t *entry = set->buckets[bucket];
	if (entry) {
		if (entry->key != hash) {
			while (entry->next) {
				entry = entry->next;
				if (!entry || entry->key == hash) {
					break;
				}
			}
		}
	} else {
		return false;
	}
	return true;
}

void set_add(set_t *set, const void *key) {
	unsigned int hash = set->hash(key);
	unsigned int bucket = hash % set->bucket_count;
	set_entry_t *entry = set->buckets[bucket];
	set_entry_t *previous = NULL;

	if (entry) {
		if (entry->key != hash) {
			while (entry->next) {
				previous = entry;
				entry = entry->next;
				if (!entry || entry->key == hash) {
					break;
				}
			}
		}
	}

	if (entry == NULL) {
		entry = calloc(1, sizeof(set_entry_t));
		entry->key = hash;
		set->buckets[bucket] = entry;
		if (previous) {
			previous->next = entry;
		}
	}
}

void set_del(set_t *set, const void *key) {
	unsigned int hash = set->hash(key);
	unsigned int bucket = hash % set->bucket_count;
	set_entry_t *entry = set->buckets[bucket];
	set_entry_t *previous = NULL;

	if (entry) {
		if (entry->key != hash) {
			while (entry->next) {
				previous = entry;
				entry = entry->next;
				if (!entry || entry->key == hash) {
					break;
				}
			}
		}
	}

	if (entry != NULL) {
		if (previous) {
			previous->next = entry->next;
		} else {
			set->buckets[bucket] = NULL;
		}
		free(entry);
	}
}
