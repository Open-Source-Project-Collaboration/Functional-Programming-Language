#include "parser.h"


parser_t new_parser(char *src)
{
	parser_t parser = {

		.state = P_PENDING,
		.lex = new_lex(src),
		.buf = new_nodebuf(strlen(src)),

	};

	/* set ast */
	parser.ast = nodebuf_next(&parser.buf);
	parser.ast->type = T_AST;

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
	if (parser->lex.type == T_EOF) {
		parser->state = P_DONE;
		return;
	} else if (parser->lex.type == T_ERR) {
		parser->state = P_ERROR;
		return;
	}

	lex_next(&parser->lex);

	node_t *next = nodebuf_next(&parser->buf);
	next->pos = parser->lex.pos;
	next->type = parser->lex.type;
	next->val = strdup(parser->lex.val);

	node_push(parser->ast, next);
	parser->state = P_REDUCE;
}


void parser_reduce(parser_t *parser)
{
	parser->state = P_SHIFT;
}