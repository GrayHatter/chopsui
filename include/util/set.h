#ifndef _SET_H
#define _SET_H

#include <stdbool.h>

typedef struct {
	unsigned int key;
	void *next;
} set_entry_t;

typedef struct {
	unsigned int (*hash)(const void *);
	set_entry_t **buckets;
	size_t bucket_count;
} set_t;

set_t *set_create(size_t buckets, unsigned int (*hash_function)(const void *));
void set_destroy(set_t *set);
void set_add(set_t *set, const void *key);
void set_del(set_t *set, const void *key);
bool set_contains(set_t *set, const void *key);

#endif
