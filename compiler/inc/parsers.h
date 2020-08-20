#ifndef FPL_COMPILER_PARSER_H
#define FPL_COMPILER_PARSER_H

#include <ctype.h>
#include <stdarg.h>
#include <unistd.h>
#include "node.h"


/* parser type */
typedef struct {
	char *src, *srci;
	pos_t pos;
} parser_t;


/* interface */
node_t *parse(char *src);


/* grammar */

/* INCOMPLETE
 * <stmt> ::= <COMMENT>
 *          | <fcall>
 *          | <expr>
 *          | <fdef>
 *          | <moduse>
 *          | <match>
 *          | <pipe>
 *          | <type>
 *          | 'pass'
 *          | <eox>
 */
node_t *parse_stmt(parser_t *p);


/* primitive parsers */
node_t *parse_COMMENT(parser_t *p);
node_t *parse_WHITESPACE(parser_t *p);


/* helper parsers */
node_t *parse_either(parser_t *p, size_t count, ...);
node_t *parse_sequence(parser_t *p, size_t count, ...);
node_t *parse_many(parser_t *p, node_t *(*parser)(parser_t *));


#endif