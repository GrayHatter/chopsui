#include <string.h>
#include <assert.h>
#include "test.h"
#include "css.h"

char *test_name = "parse/stylesheet_parse";

static int test_comments() {
	stylesheet_t *ss = stylesheet_parse("/* this should cause\n"
			"a syntax error if comments aren't being handled\n"
			"correctly. */");
	stylesheet_destroy(ss);
	return 0;
}

int test_main() {
	return test_comments()
	;
}
