#include "node.h"


node_t new_node(pos_t pos, ttype_t type, char *val)
{
	return (node_t) {
		.pos = pos,
		.type = type,
		.val = val,

		.vec = new_nodevec()
	};
}


void free_node(node_t *node)
{
	free(node->val);
	free_nodevec(&node->vec);
}


void print_node(node_t *node)
{
	return _print_node(node, 0);
}


void _print_node(node_t *node, size_t indent)
{
	size_t i = 0;
	while (i++ < indent)
		putchar('\t');

	printf(
		"{%lu, %lu} -> %s '%s'\n",
		node->pos.x,
		node->pos.y,
		ttype_str[node->type],
		node->val
	);

	for (i = 0; i < node->vec.len; i++)
		_print_node(node->vec.ns[i], indent + 1);
}