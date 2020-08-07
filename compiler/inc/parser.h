#ifndef FPL_COMPILER_PARSER_H
#define FPL_COMPILER_PARSER_H

#include <stdarg.h>
#include "lexer.h"
#include "is_functions.h"
#include "node.h"


/* parser state */
typedef enum {
	P_PENDING,
	P_ERROR,
	P_DONE,
	P_SHIFT,
	P_REDUCE
} pstate_t;

/* parser */
typedef struct {

	/* parser state */
	pstate_t state;
	lex_t lex;
	node_t ast;

} parser_t;

/* constructor & destructor */
parser_t new_parser(char *src);
void free_parser(parser_t *parser);

/* methods */
bool parser_match(parser_t *parser, size_t count, ...);
void parser_shift(parser_t *parser);
void parser_reduce(parser_t *parser);


#endif