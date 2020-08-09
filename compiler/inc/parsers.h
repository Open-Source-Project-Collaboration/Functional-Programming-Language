#ifndef FPL_COMPILER_PARSER_H
#define FPL_COMPILER_PARSER_H

#include <stdarg.h>
#include <unistd.h>
#include "lexer.h"
#include "node.h"


/* interface */
node_t *parse(lex_t *lex);


/* <array> ::= "[" <pair> "]" */
node_t *parse_array(lex_t *lex);


/* [INCOMPLETE]
 * <pair> ::= <pipe> ";" <pair>
 *          | <pipe> ";" <pipe>
 */
node_t *parse_pair(lex_t *lex);


/*
 * <literal> ::= <NAME>
 *             | <INT>
 *             | <FLOAT>
 *             | <STR>
 *             | <BOOL>
 *             | <array>
 */
node_t *parse_literal(lex_t *lex);


/* helpers */
node_t *parse_many(lex_t *lex, node_t *(*fn)(lex_t *));
node_t *parse_sequence(lex_t *lex, size_t count, ...);
node_t *parse_either(lex_t *lex, size_t count, ...);


#endif