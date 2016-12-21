#ifndef _SUI_CSS_H
#define _SUI_CSS_H

#include <stdio.h>
#include "util/list.h"
#include "util/hashtable.h"
#include "scalars.h"

enum selector_type {
	SELECTOR_TYPE,         // type
	SELECTOR_ID,           // #id
	SELECTOR_CLASS,        // .class
	SELECTOR_ATTRIBUTE,    // [...]
	SELECTOR_DESCENDANT,   // (whitespace)
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

enum media_rule_feature {
	MEDIA_FEAT_WIDTH,
	MEDIA_FEAT_HEIGHT,
	MEDIA_FEAT_ASPECT_RATIO,
	MEDIA_FEAT_ORIENTATION,
	MEDIA_FEAT_RESOLUTION,
	MEDIA_FEAT_HOVER,
};

enum media_rule_type {
	MEDIA_TYPE_MIN,
	MEDIA_TYPE_MAX,
};

enum media_rule_operator {
	MEDIA_OP_OR,
	MEDIA_OP_AND,
	MEDIA_OP_NOT,
	MEDIA_OP_ONLY,
};

struct media_rule {
	enum media_rule_feature feature;
	enum media_rule_type type;
	enum media_rule_operator operator;
	sui_scalar_t scalar;
	struct media_rule *next;
};

typedef struct media_rule media_rule_t;

struct keyframe {
	scalar_t at;
	list_t *rules;
};

struct keyframes {
	char *identifier;
	list_t *keys;
};

typedef struct keyframes keyframes_t;

struct stylesheet {
	list_t *rules;
	list_t *media_rules;
	list_t *keyframes;
};

typedef struct stylesheet stylesheet_t;

stylesheet_t *stylesheet_parse(const char *source);
stylesheet_t *stylesheet_parsef(FILE *source);

#endif
