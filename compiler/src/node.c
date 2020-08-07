#include "node.h"


#define FPL_DEFAULT_NS_CAP 20


node_t new_node(pos_t pos, ttype_t type, char *val)
{
	return (node_t) {
		.pos = pos,
		.type = type,
		.val = val,

		.ns = calloc(FPL_DEFAULT_NS_CAP, sizeof(node_t*)),
		.ns_len = 0,
		.ns_cap = FPL_DEFAULT_NS_CAP
	};
}


void free_node(node_t *node)
{
	free(node->val);
	free(node->ns);
}


void node_push(node_t *node, node_t *child)
{
	if (node->ns_len > node->ns_cap / 2) {
		node->ns_cap *= 2;
		node->ns = realloc(node->ns, node->ns_cap * sizeof(node_t *));
	}

	node->ns[node->ns_len++] = node;
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