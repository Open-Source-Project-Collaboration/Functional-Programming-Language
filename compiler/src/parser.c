#include "parser.h"


parser_t new_parser(char *src)
{
	parser_t parser = {

		.state = P_PENDING,
		.lex = new_lex(src)

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
}


bool parser_match(parser_t *parser, size_t count, ...)
{
	return false;
}


void parser_shift(parser_t *parser)
{
	parser->state = P_DONE;
}


void parser_reduce(parser_t *parser)
{
	parser->state = P_DONE;
}