#include <stdbool.h>
#include "ttype.h"


#define X(t) bool is_##t(ttype_t type);
	TTYPES
#undef X