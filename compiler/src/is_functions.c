#include "is_functions.h"


#define X(t)\
bool is_##t(ttype_t type)\
{\
	return T_##t == type;\
}

TTYPES


bool is_dotop(ttype_t type)
{
	return type == T_DOTOP || type == T_NAME;
}

bool is_primitive(ttype_t type)
{
	return type >= T_NAME && type <= T_ARRAY;
}


#undef X