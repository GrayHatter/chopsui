#ifndef _SUI_CSS_H
#define _SUI_CSS_H

#include <stdio.h>
#include "util/list.h"
#include "util/hashtable.h"

enum selector_type {
	SELECTOR_INVALID,      // for internal use
	SELECTOR_TYPE,         // type
	SELECTOR_ID,           // #id
	SELECTOR_CLASS,        // .class
	SELECTOR_ATTRIBUTE,    // [...]
	SELECTOR_CHILD,        // >
	SELECTOR_SIBLING,      // ~
	SELECTOR_NEXT_SIBLING, // +
};

enum attribute_comparison {
	ATTR_EXISTS,         // [attr] matches attr="*"
	ATTR_EQUALS,         // [attr=value] matches attr="word"
	ATTR_WORD,           // [attr~=word] matches attr="x x word x x"
	ATTR_EQUALS_OR_DASH, // [attr|=word] matches attr="word" or attr="word-*"
	ATTR_PREFIX,         // [attr^=prefix] matches attr="prefix*"
	ATTR_SUFFIX,         // [attr$=suffix] matches attr="*suffix"
	ATTR_CONTAINS,       // [attr*=match] matches attr="*match*"
};

struct selector {
	struct selector *next;

	enum selector_type type;
	char *value;

	// Used for attribute selectors
	enum attribute_comparison comparison;
	char *attr_value;
};

typedef struct selector *selector_t;

/**
 * Parses a selector string and returns a new selector.
 */
selector_t selector_parse(const char *source);

/**
 * Frees a selector.
 */
void selector_destroy(selector_t selector);

struct style_property {
	char *name;
	char *value;
};

struct style_rule {
	// Type: 0
	// Class: 1
	// ID: 2
	int specificity;
	list_t *selectors;
	hashtable_t *properties;
};

typedef struct style_rule style_rule_t;

struct stylesheet {
	list_t *rules;
};

typedef struct stylesheet stylesheet_t;

stylesheet_t *stylesheet_parse(const char *source);
stylesheet_t *stylesheet_parsef(FILE *source);

#endif
