#ifndef FPL_COMPILER_IS_FUNCTIONS_H
#define FPL_COMPILER_IS_FUNCTIONS_H

#include <stdbool.h>
#include "ttype.h"


#define X(t) bool is_##t(ttype_t type);
	TTYPES
#undef X


#endif