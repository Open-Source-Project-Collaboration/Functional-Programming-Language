#include "lexer.h"


lex_t new_lex(char *src)
{
	char *buf = strdup(src);
	*buf = '\0';

	return (lex_t) {
		.src = src, .srci = src,
		.buf = buf, .bufi = buf,
		.ipos = {1, 1},

		.pos = {1, 1},
		.type = T_PENDING,
		.val = NULL,

		.i_len = 0, .i_dep = 0
	};
}


void free_lex(lex_t *lex)
{
	free(lex->src);
	free(lex->buf);
}



void lex_print(lex_t *lex)
{
	printf(
		"{%lu, %lu} -> %s '%s'\n",
		lex->pos.x,
		lex->pos.y,
		ttype_str[lex->type],
		lex->val
	);
}


void lex_next(lex_t *lex)
{
	lex->type = T_EOF;
}