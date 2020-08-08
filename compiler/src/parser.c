#include "parser.h"


parser_t new_parser(char *src)
{
	parser_t parser = {
		.lex = new_lex(src),
		.ast = new_node((pos_t){0, 0}, T_AST, NULL)
	};

	/* parse the thing */
	parser_parse(&parser);
	return parser;
}


void free_parser(parser_t *parser)
{
	free_lex(&parser->lex);
	free_node(&parser->ast);
}


void parser_parse(parser_t *parser)
{
}