#ifndef FPL_COMPILER_LEXER_H
#define FPL_COMPILER_LEXER_H

#include <ctype.h>
#include "common.h"
#include "helpers.h"
#include "ttype.h"


/* lexer */
typedef struct {
	char *src, *srci;
	pos_t ipos;

	pos_t pos;
	ttype_t type;
	char *val, *vali;

	size_t i_len, i_dep;
} lex_t;

/* constructor & destructor */
lex_t new_lex(char *src);
void free_lex(lex_t *lex);

/* methods */
void lex_print(lex_t *lex);
void lex_next(lex_t *lex);
ttype_t lex_peek(lex_t *lex);


#endif