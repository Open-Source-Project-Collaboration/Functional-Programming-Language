#include "nodebuf.h"


nodebuf_t new_nodebuf(size_t cap)
{
	return (nodebuf_t) {
		.ns = calloc(cap, sizeof(node_t)),
		.len = 0,
		.cap = cap
	};
}


void free_nodebuf(nodebuf_t *buf)
{
	size_t i;
	for (i = 0; i < buf->len; i++)
		free_node(buf->ns + i);
}


node_t *nodebuf_next(nodebuf_t *buf)
{
	if (buf->len >= buf->cap)
		return NULL;

	return buf->ns + buf->len++;
}