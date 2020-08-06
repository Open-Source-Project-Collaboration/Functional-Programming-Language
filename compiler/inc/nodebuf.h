#ifndef FPL_COMPILER_NODEBUF_H
#define FPL_COMPILER_NODEBUF_H

#include <stdlib.h>
#include "node.h"


/* node buffer */
typedef struct {
	node_t *ns;
	size_t len, cap;
} nodebuf_t;

/* constructor & destructor */
nodebuf_t new_nodebuf(size_t cap);
void free_nodebuf(nodebuf_t *buf);

/* methods */
node_t *nodebuf_next(nodebuf_t *buf);


#endif