#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "scalars.h"

bool scalar_parse(const char *s, sui_scalar_t *scalar) {
	char *unit;
	if (strchr(s, '.')) {
		scalar->fval = strtod(s, &unit);
		scalar->type = SCALAR_FLOAT;
	} else {
		scalar->ival = strtol(s, &unit, 10);
		scalar->type = SCALAR_INT;
	}
	if (unit == s) {
		uint32_t color;
		bool valid = color_parse(s, &color);
		scalar->uval = color;
		scalar->type = SCALAR_COLOR;
		return valid;
	}
	if (!*unit) {
		// Is an int or a float with no unit
		return true;
	}
	struct type_map {
		char *str;
		enum scalar_type base;
		enum scalar_type type;
	};
	struct type_map maps[] = {
		{ "dpi", SCALAR_FLOAT, SCALAR_DPI },
		{ "em", SCALAR_FLOAT, SCALAR_EM },
		{ "rem", SCALAR_FLOAT, SCALAR_REM },
		{ "px", SCALAR_INT, SCALAR_PX },
		{ "%", SCALAR_FLOAT, SCALAR_PERCENT },
		{ "deg", SCALAR_FLOAT, SCALAR_DEG },
		{ "rad", SCALAR_FLOAT, SCALAR_RAD },
		{ "grad", SCALAR_FLOAT, SCALAR_GRAD },
		{ "ms", SCALAR_FLOAT, SCALAR_MS },
		{ "s", SCALAR_FLOAT, SCALAR_S },
		{ "hz", SCALAR_FLOAT, SCALAR_HZ },
		{ "khz", SCALAR_FLOAT, SCALAR_KHZ },
	};
	for (size_t i = 0; i < sizeof(maps) / sizeof(struct type_map); ++i) {
		if (strcasecmp(maps[i].str, unit) == 0) {
			if (scalar->type == SCALAR_FLOAT && maps[i].base == SCALAR_INT) {
				// Not allowed to demote float to int
				return false;
			}
			if (scalar->type == SCALAR_INT && maps[i].base == SCALAR_FLOAT) {
				// Promote int to float
				scalar->fval = (float)scalar->ival;
			}
			scalar->type = maps[i].type;
			return true;
		}
	}
	// Invalid unit
	return false;
}
