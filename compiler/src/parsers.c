#include "parsers.h"


node_t *parse(lex_t *lex)
{
	node_t *parsed = NULL;
	return parsed;
}


node_t *parse_many(lex_t *lex, node_t *(*fn)(lex_t *))
{
	node_t *many = new_node((pos_t){0, 0}, T_STMT, NULL);
	node_t *single = NULL;

	while (single = fn(lex))
		node_push(many, single);

	return many;
}


node_t *parse_sequence(lex_t *lex, size_t count, ...)
{
	char *backup = lex->srci;
	node_t *seq = new_node((pos_t){0, 0}, T_STMT, NULL);

	va_list args;
	va_start(args, count);

	while (count != 0) {
		lex->srci = backup;

		node_t *(*parse_x)(lex_t *) = va_arg(args, node_t *(*)(lex_t *));

		node_t *parsed = parse_x(lex);
		if (parsed == NULL) {
			lex->srci = backup;
			free_node(seq);
			va_end(args);
			return NULL;
		}

		node_push(seq, parsed);
		--count;
	}

	va_end(args);
	return seq;
}


node_t *parse_either(lex_t *lex, size_t count, ...)
{
	char *backup = lex->srci;

	va_list args;
	va_start(args, count);

	while (count != 0) {
		lex->srci = backup;

		node_t *(*parse_x)(lex_t *) = va_arg(args, node_t *(*)(lex_t *));

		node_t *parsed = parse_x(lex);
		if (parsed != NULL) {
			va_end(args);
			return parsed;
		}

		--count;
	}

	va_end(args);
	return NULL;
}