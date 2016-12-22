#include <string.h>
#include <assert.h>
#include "test.h"
#include "internal/colors.h"

char *test_name = "util/get_named_color";

int test_main() {
	uint32_t c;
	assert(get_named_color("black", &c));
	assert(c == 0xFF000000);
	assert(get_named_color("white", &c));
	assert(c == 0xFFFFFFFF);
	assert(get_named_color("rebeccapurple", &c));
	assert(c == 0xFF663399);
	assert(!get_named_color("nonexistent color", &c));
	return 0;
}
