#include "nodevec.h"


#define FPL_DEFAULT_NODEVEC_CAP 20


nodevec_t new_nodevec()
{
	node_t *ns = calloc(FPL_DEFAULT_NODEVEC_CAP, sizeof(node_t*));
	return (nodevec_t) {
		.ns = ns,
		.len = 0,
		.cap = FPL_DEFAULT_NODEVEC_CAP
	};
}


void free_nodevec(nodevec_t *nodevec)
{
	free(nodevec->ns);
}


void nodevec_push(nodevec_t *nodevec, node_t *node)
{
	if (nodevec->len > nodevec->cap / 2) {
		nodevec->cap *= 2;
		nodevec->ns = realloc(nodevec->ns, nodevec->cap * sizeof(node_t *));
	}

	nodevec->ns[nodevec->len++] = node;
}


node_t *nodevec_pop(nodevec_t *nodevec)
{
	return nodevec->ns[--nodevec->len];
}


node_t *nodevec_top(nodevec_t *nodevec)
{
	return nodevec->ns[nodevec->len - 1];
}