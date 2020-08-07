#include "parser.h"


parser_t new_parser(char *src)
{
	parser_t parser = {

		.state = P_PENDING,
		.lex = new_lex(src),
		.ast = new_node((pos_t){0, 0}, T_AST, NULL)

	};

	/* parse the thing */
	parser.state = P_SHIFT;
	while (parser.state != P_DONE) {
		if (parser.state == P_SHIFT) {
			parser_shift(&parser);
		} else if (parser.state == P_REDUCE) {
			parser_reduce(&parser);
		} else if (parser.state == P_ERROR) {
			lex_print(&parser.lex);
			break;
		}
	}

	return parser;
}


void free_parser(parser_t *parser)
{
	free_lex(&parser->lex);
	free_node(&parser->ast);
}


bool parser_match(parser_t *parser, size_t count, ...)
{
	if (count >= parser->ast.ns_len)
		return false;

	va_list args;
	va_start(args, count);

	while (count != 0) {
		bool (*type_is)(ttype_t) = va_arg(args, bool (*)(ttype_t));

		size_t expected_idx = parser->ast.ns_len - count - 1;
		ttype_t expected = parser->ast.ns[expected_idx].type;

		if (type_is(expected) == false) {
			va_end(args);
			return false;
		}

		count--;
	}

	va_end(args);
	return true;
}


void parser_shift(parser_t *parser)
{
	lex_next(&parser->lex);

	if (parser->lex.type == T_EOF) {
		parser->state = P_DONE;
		return;
	} else if (parser->lex.type == T_ERR) {
		parser->state = P_ERROR;
		return;
	}


	node_t next = new_node(
		parser->lex.pos,
		parser->lex.type,
		strdup(parser->lex.val)
	);

	node_push(&parser->ast, next);
	parser->state = P_REDUCE;
}


void parser_reduce(parser_t *parser)
{
	parser->state = P_DONE;
}