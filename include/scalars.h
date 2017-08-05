#ifndef _SUI_SCALARS_H
#define _SUI_SCALARS_H

#include <stdint.h>
#include <stdbool.h>

enum scalar_type {
	SCALAR_EMPTY,
	SCALAR_INT,
	SCALAR_FLOAT,
	SCALAR_DPI,
	SCALAR_EM,
	SCALAR_REM,
	SCALAR_PX,
	SCALAR_PERCENT,
	SCALAR_DEG,
	SCALAR_RAD,
	SCALAR_GRAD,
	SCALAR_MS,
	SCALAR_S,
	SCALAR_HZ,
	SCALAR_KHZ,
	SCALAR_COLOR,
	SCALAR_BOOL,
	SCALAR_CHAR,
	SCALAR_VOID,
};

struct sui_scalar {
	enum scalar_type type;
	union {
		bool bval;
		double fval;
		long ival;
		unsigned long uval;
		struct {
			uint8_t a, b, g, r;
		};
		char *str;
		void *data;
	};
};

/**
 * Parses a CSS scalar string into a sui_scalar_t
 */
bool scalar_parse(const char *s, struct sui_scalar *scalar);

/**
 * Parses a CSS color string into a uint32_t
 */
bool color_parse(const char *str, uint32_t *val);

struct display_info {
	double font_size;
	double root_font_size;
};

/**
 * Normalizes the units of a sui_scalar, optionally normalizing pixels with
 * the provided display information.
 *
 * The provided scalar will be reduced to the following units:
 *
 * - SCALAR_INT
 * - SCALAR_FLOAT
 * - SCALAR_DPI
 * - SCALAR_PX
 * - SCALAR_PERCENT
 * - SCALAR_RAD
 * - SCALAR_S
 * - SCALAR_HZ
 * - SCALAR_COLOR
 */
void scalar_normalize(struct sui_scalar *scalar, struct display_info *info);

#endif
