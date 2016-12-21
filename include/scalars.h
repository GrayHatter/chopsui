#ifndef _SUI_SCALARS_H
#define _SUI_SCALARS_H

#include <stdint.h>
#include <stdbool.h>

enum scalar_type {
	SCALAR_INT,
	SCALAR_FLOAT,
	SCALAR_DPI,
	SCALAR_EM,
	SCALAR_REM,
	SCALAR_PX,
	SCALAR_PERCENT,
};

struct sui_scalar {
	enum scalar_type type;
	union {
		double fval;
		long ival;
	};
};

typedef struct sui_scalar sui_scalar_t;

bool scalar_parse(const char *s, sui_scalar_t *scalar);

#endif
