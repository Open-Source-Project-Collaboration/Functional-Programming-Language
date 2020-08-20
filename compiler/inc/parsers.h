#ifndef FPL_COMPILER_PARSER_H
#define FPL_COMPILER_PARSER_H

#include <stdarg.h>
#include <unistd.h>
#include "node.h"


/* interface */
node_t *parse(char *src);


#endif