#include "parsers.h"


node_t *parse(char *src)
{
	parser_t p = {
		.src = src, .srci = src,
		.pos = {1, 1}
	};

	return parse_many(&p, parse_stmt);
}


node_t *parse_stmt(parser_t *p)
{
	return parse_either(
		p, 1,
		parse_COMMENT
	);
}


node_t *parse_COMMENT(parser_t *p)
{
	parse_WHITESPACE(p);

	if (*p->srci != '#')
		return NULL;

	while (*p->srci != '\n')
		p->srci++, p->pos.x++;

	return NULL;
}


node_t *parse_WHITESPACE(parser_t *p)
{
	while (isspace(*p->srci))
		p->srci++;
	return NULL;
}


node_t *parse_either(parser_t *p, size_t count, ...)
{
	va_list args;
	va_start(args, count);

	node_t *parsed = NULL;

	while (count != 0) {
		node_t *(*parser)(parser_t *) = va_arg(args, node_t *(*)(parser_t *));

		if ((parsed = parser(p)) != NULL)
			break;

		count--;
	}

	va_end(args);
	return parsed;
}


node_t *parse_sequence(parser_t *p, size_t count, ...)
{
	va_list args;
	va_start(args, count);

	node_t *stmts = new_node(p->pos, T_STMTS, NULL);
	char *backup = p->srci;

	while (count != 0) {
		node_t *(*parser)(parser_t *) = va_arg(args, node_t *(*)(parser_t *));

		node_t *parsed = parser(p);
		if (parsed == NULL) {
			p->srci = backup;
			free_node(stmts);
			stmts = NULL;
			break;
		}

		node_push(stmts, parsed);
		count--;
	}

	va_end(args);
	return stmts;
}


node_t *parse_many(parser_t *p, node_t *(*parser)(parser_t *))
{
	node_t *stmts = new_node(p->pos, T_STMTS, NULL);

	node_t *parsed;
	while ((parsed = parser(p)) != NULL)
		node_push(stmts, parsed);

	return stmts;
}