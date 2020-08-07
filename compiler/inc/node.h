#ifndef FPL_COMPILER_NODE_H
#define FPL_COMPILER_NODE_H

#include <stdio.h>
#include "common.h"
#include "ttype.h"


/* node */
typedef struct node_t node_t;
struct node_t {

	/* token */
	pos_t pos;
	ttype_t type;
	char *val;

	/* children */
	node_t **ns;
	size_t ns_len, ns_cap;

};

/* constructor & destructor */
node_t new_node(pos_t pos, ttype_t type, char *val);
void free_node(node_t *node);

/* methods */
void node_push(node_t *node, node_t *child);

/* debug methods */
void print_node(node_t *node);
void _print_node(node_t *node, size_t indent);


#endif