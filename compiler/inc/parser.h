#ifndef FPL_COMPILER_PARSER_H
#define FPL_COMPILER_PARSER_H

#include <stdarg.h>
#include <unistd.h>
#include "lexer.h"
#include "node.h"


/* parser */
typedef struct {

	/* parser state */
	lex_t lex;
	node_t ast;

} parser_t;

/* constructor & destructor */
parser_t new_parser(char *src);
void free_parser(parser_t *parser);

/* methods */
void parser_parse(parser_t *parser);


#endif