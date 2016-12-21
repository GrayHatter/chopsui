#include <string.h>
#include <assert.h>
#include "test.h"
#include "scalars.h"

char *test_name = "parse/scalar_parse";

static int test_unitless_int() {
	sui_scalar_t scalar;
	assert(scalar_parse("1234", &scalar));
	assert(scalar.type == SCALAR_INT);
	assert(scalar.ival == 1234);
	return 0;
}

static int test_unitless_float() {
	sui_scalar_t scalar;
	assert(scalar_parse("12.34", &scalar));
	assert(scalar.type == SCALAR_FLOAT);
	assert(scalar.fval == 12.34);
	return 0;
}

static int test_simple_unit_cases() {
	sui_scalar_t scalar;
	assert(scalar_parse("1234px", &scalar));
	assert(scalar.type == SCALAR_PX);
	assert(scalar.ival == 1234);

	assert(scalar_parse("12.34rem", &scalar));
	assert(scalar.type == SCALAR_REM);
	assert(scalar.fval == 12.34);
	return 0;
}

static int test_int_promotion() {
	sui_scalar_t scalar;
	assert(scalar_parse("1234rem", &scalar));
	assert(scalar.type == SCALAR_REM);
	assert(scalar.fval == 1234);
	return 0;
}

static int test_float_demotion() {
	sui_scalar_t scalar;
	assert(!scalar_parse("12.34px", &scalar));
	return 0;
}

static int test_error_cases() {
	sui_scalar_t scalar;
	assert(!scalar_parse("rem", &scalar));
	assert(!scalar_parse("10.20.30", &scalar));
	assert(!scalar_parse("100units", &scalar));
	return 0;
}

int test_main() {
	return test_unitless_int()
		|| test_unitless_float()
		|| test_simple_unit_cases()
		|| test_int_promotion()
		|| test_float_demotion()
		|| test_error_cases()
	;
}
