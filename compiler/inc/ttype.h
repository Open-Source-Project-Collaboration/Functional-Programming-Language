/*
 * This file containes the list of token types
 */

#ifndef FPL_COMPILER_TTYPE_H
#define FPL_COMPILER_TTYPE_H


/* list of tokens */
#define TTYPES\
	X(PENDING)\
	X(ERR)\
	X(EOF)\
	X(LAST)


/* convert to enum */
typedef enum {
	#define X(t) T_##t,
		TTYPES
	#undef X
} ttype_t;


/* convert to string */
static const char *ttype_str[] = {
	#define X(t) #t,
		TTYPES
	#undef X
};


#endif