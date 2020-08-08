#ifndef FPL_COMPILER_PARSER_H
#define FPL_COMPILER_PARSER_H

#include <stdarg.h>
#include <unistd.h>
#include "lexer.h"
#include "node.h"


/* parsers */
void parse_statements(lex_t *lex);
void parse_statement(lex_t *lex);


#endif