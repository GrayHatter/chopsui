#define _XOPEN_SOURCE
#include <stdlib.h>
#include <math.h>
#include "scalars.h"

void scalar_normalize(struct sui_scalar *scalar, struct display_info *info) {
	switch (scalar->type) {
	case SCALAR_EM:
		if (info) {
			scalar->type = SCALAR_PX;
			scalar->fval *= info->font_size;
		}
		break;
	case SCALAR_REM:
		if (info) {
			scalar->type = SCALAR_PX;
			scalar->fval *= info->root_font_size;
		}
		break;
	case SCALAR_DEG:
		scalar->type = SCALAR_RAD;
		scalar->fval = scalar->fval / (360 / M_2_PI);
		break;
	case SCALAR_GRAD:
		// TODO: Implement this once I have internet to tell me wtf grads are
		break;
	case SCALAR_MS:
		scalar->type = SCALAR_S;
		scalar->fval /= 1000.0;
		break;
	case SCALAR_KHZ:
		scalar->type = SCALAR_HZ;
		scalar->fval /= 1000.0;
		break;
	default:
		return;
	}
}
