#include "is_functions.h"


#define X(t)\
bool is_##t(ttype_t type)\
{\
	return T_##t == type;\
}

TTYPES

#undef X