#ifndef FPL_COMPILER_NODE_H
#define FPL_COMPILER_NODE_H

#include "common.h"
#include "ttype.h"
#include "nodevec.h"


/* node */
typedef struct node_t node_t;
struct node_t {

	/* token */
	pos_t pos;
	ttype_t type;
	char *val;

	/* children */
	nodevec_t vec;

};

/* constructor & destructor */
node_t new_node(pos_t pos, ttype_t type, char *val);
void free_node(node_t *node);

/* debug methods */
void print_node(node_t *node);
void _print_node(node_t *node, size_t indent);


#endif