#include <string.h>
#include <assert.h>
#include "test.h"
#include "util/unicode.h"

char *test_name = "util/unicode";

static int test_utf8_decode() {
	const char *test = "こんにちわ";
	const char *str = test;
	assert(utf8_decode(&test) == 0x3053);
	assert(test == str + 3);
	assert(utf8_decode(&test) == 0x3093);
	assert(utf8_decode(&test) == 0x306B);
	assert(utf8_decode(&test) == 0x3061);
	assert(utf8_decode(&test) == 0x308F);
	return 0;
}

static int test_utf8_encode() {
	char test[128];
	char *str = test;
	str += utf8_encode(str, 0x3053);
	assert(str == test + 3);
	str += utf8_encode(str, 0x3093);
	str += utf8_encode(str, 0x306B);
	str += utf8_encode(str, 0x3061);
	str += utf8_encode(str, 0x308F);
	*str = '\0';
	assert(strcmp(test,  "こんにちわ") == 0);
	return 0;
}

int test_main() {
	return test_utf8_decode()
		|| test_utf8_encode()
	;
}
