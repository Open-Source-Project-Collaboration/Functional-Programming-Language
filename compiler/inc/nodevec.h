#ifndef FPL_COMPILER_NODEVEC_H
#define FPL_COMPILER_NODEVEC_H

#include <stdlib.h>
#include "node.h"


/* node vector */
typedef struct {
	node_t **ns;
	size_t len, cap;
} nodevec_t;

/* constructor & destructor */
nodevec_t new_nodevec();
void free_nodevec(nodevec_t *nodevec);

/* methods */
void nodevec_push(nodevec_t *nodevec, node_t *node);
node_t *nodevec_pop(nodevec_t *nodevec);
node_t *nodevec_top(nodevec_t *nodevec);


#endif