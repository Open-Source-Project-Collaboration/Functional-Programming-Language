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

		/* debug */
		/* print_node(&parser.ast), sleep(2); */
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
	if (count > parser->ast.ns_len)
		return false;

	va_list args;
	va_start(args, count);

	while (count != 0) {
		bool (*is_type)(ttype_t) = va_arg(args, bool (*)(ttype_t));

		size_t expected_idx = parser->ast.ns_len - count;
		ttype_t expected = parser->ast.ns[expected_idx].type;

		if (is_type(expected) == false) {
			va_end(args);
			return false;
		}

		--count;
	}

	va_end(args);
	return true;
}


void parser_push(parser_t *parser, node_t node)
{
	return node_push(&parser->ast, node);
}


node_t parser_pop(parser_t *parser)
{
	return node_pop(&parser->ast);
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
	/* 
	 * dotop <- dotop '.' NAME
         *        | NAME '.' NAME
         *        | NAME
	 */
	if (parser_match(parser, 3, is_dotop, is_DOT, is_NAME)) {
		node_t name = parser_pop(parser);
		node_t dot = parser_pop(parser);
		node_t dotop = parser_pop(parser);

		dot.type = T_DOTOP;
		node_push(&dot, dotop);
		node_push(&dot, name);

		parser_push(parser, dot);
	}

	parser->state = P_SHIFT;
}