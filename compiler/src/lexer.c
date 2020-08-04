#include "lexer.h"


lex_t new_lex(char *src)
{
	char *buf = strdup(src);
	*buf = '\0';

	return (lex_t) {
		.src = src, .srci = src,
		.ipos = {1, 1},

		.pos = {1, 1},
		.type = T_PENDING,
		.val = buf, .vali = buf,

		.i_len = 0, .i_dep = 0
	};
}


void free_lex(lex_t *lex)
{
	free(lex->src);
	free(lex->val);
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
	/* check iterator */
	if (lex->type == T_ERR || lex->type == T_EOF)
		return;

	/* reset buffer */
	lex->vali = lex->val;

	/* skip whitespace */
	while (*lex->srci == ' ' || *lex->srci == '\t')
		lex->srci++, lex->ipos.x++;

	/* get the start pos */
	lex->pos = lex->ipos;

	/* comments */
	if (*lex->srci == '#') {
		while (*lex->srci++ != '\n')
			;

		lex->ipos.y++;
		lex->ipos.x = 1;

		lex_next(lex);
	}

	/* indentation/newlines */
	else if (*lex->srci == '\n') {
		while (*lex->srci == '\n')
			lex->srci++, lex->ipos.y++;
		lex->ipos.x = 1;

		size_t i_len = 0;
		while (*lex->srci == ' ' || *lex->srci == '\t') {
			i_len++;
			if (*lex->srci++ == '\t')
				i_len += 7;
			lex->ipos.x++;
		}

		if (i_len > lex->i_len) {
			lex->i_dep++;
			lex->type = T_INDENT;
		} else if (i_len < lex->i_len) {
			lex->i_dep--;
			lex->type = T_DEDENT;
		} else {
			lex->type = T_EOL;
		}

		lex->i_len = i_len;
	}

	/* names */
	else if (isalpha(*lex->srci) || *lex->srci == '_') {
		while (isalpha(*lex->srci) || *lex->srci == '_' || isdigit(*lex->srci))
			*lex->vali++ = *lex->srci++, lex->ipos.x++;
		*lex->vali = '\0';

		if (strcmp(lex->val, "true") == 0)
			lex->type = T_BOOL, strcpy(lex->val, " ");
		else if (strcmp(lex->val, "false") == 0)
			lex->type = T_BOOL, *lex->val = '\0';
		else if (strcmp(lex->val, "let") == 0)
			lex->type = T_LET;
		else if (strcmp(lex->val, "for") == 0)
			lex->type = T_FOR;
		else if (strcmp(lex->val, "while") == 0)
			lex->type = T_WHILE;
		else if (strcmp(lex->val, "mut") == 0)
			lex->type = T_MUT;
		else if (strcmp(lex->val, "mod") == 0)
			lex->type = T_MOD;
		else if (strcmp(lex->val, "use") == 0)
			lex->type = T_USE;
		else if (strcmp(lex->val, "type") == 0)
			lex->type = T_TYPE;
		else if (strcmp(lex->val, "match") == 0)
			lex->type = T_MATCH;
		else if (strcmp(lex->val, "in") == 0)
			lex->type = T_IN;
		else if (strcmp(lex->val, "and") == 0)
			lex->type = T_AND;
		else if (strcmp(lex->val, "or") == 0)
			lex->type = T_OR;
		else
			lex->type = T_NAME;
	}

	/* numbers */
	else if (isdigit(*lex->srci) || (*lex->srci == '.' && isdigit(*(lex->srci + 1)))) {
		lex->type = T_INT;

		if (*lex->srci == '.') {
			lex->type = T_FLOAT;
			*lex->vali++ = *lex->srci++;
			lex->ipos.x++;
		}

		while (isdigit(*lex->srci) || *lex->srci == '.') {
			if (lex->type == T_FLOAT && *lex->srci == '.')
				break;
			else if (*lex->srci == '.')
				lex->type = T_FLOAT;

			*lex->vali++ = *lex->srci++;
			lex->ipos.x++;
		}
		*lex->vali = '\0';
	}

	/* strings */
	else if (*lex->srci == '\'' || *lex->srci == '\"') {
		const char pair = *lex->srci++;

		while (*lex->srci != pair) {
			if (*lex->srci == '\n') {
				lex->type = T_ERR;
				strcpy(lex->val, "Strings can't have newlines in them");
				return;
			} else if (*lex->srci == '\0') {
				lex->type = T_ERR;
				strcpy(lex->val, "String quotes must match, unfinished string found");
				return;
			}

			*lex->vali++ = *lex->srci++;
			lex->ipos.x++;
		}
		*lex->vali = '\0';
		lex->srci++;
		lex->ipos.x++;

		lex->type = T_STR;
	}

	/* punctuation */
	else if (*lex->srci == ':')
		lex->srci++, lex->ipos.x++, lex->type = T_COLON;
	else if (*lex->srci == '.')
		lex->srci++, lex->ipos.x++, lex->type = T_DOT;
	else if (*lex->srci == '(')
		lex->srci++, lex->ipos.x++, lex->type = T_LPAR;
	else if (*lex->srci == ')')
		lex->srci++, lex->ipos.x++, lex->type = T_RPAR;
	else if (*lex->srci == '[')
		lex->srci++, lex->ipos.x++, lex->type = T_LBRAC;
	else if (*lex->srci == ']')
		lex->srci++, lex->ipos.x++, lex->type = T_RBRAC;
	else if (*lex->srci == ';')
		lex->srci++, lex->ipos.x++, lex->type = T_SEMI;
	else if (*lex->srci == '|' && *(lex->srci + 1) == '>')
		lex->srci += 2, lex->ipos.x += 2, lex->type = T_PIPE;
	else if (*lex->srci == '|')
		lex->srci++, lex->ipos.x++, lex->type = T_BAR;
	else if (*lex->srci == '=' && *(lex->srci + 1) == '>')
		lex->srci += 2, lex->ipos.x += 2, lex->type = T_ARROW;

	/* logic ops */
	else if (*lex->srci == '=' && *(lex->srci + 1) == '=')
		lex->srci += 2, lex->ipos.x += 2, lex->type = T_DEQ;
	else if (*lex->srci == '!' && *(lex->srci + 1) == '=')
		lex->srci += 2, lex->ipos.x += 2, lex->type = T_NOTEQ;
	else if (*lex->srci == '<' && *(lex->srci + 1) == '=')
		lex->srci += 2, lex->ipos.x += 2, lex->type = T_LESSEQ;
	else if (*lex->srci == '<')
		lex->srci++, lex->ipos.x++, lex->type = T_LESS;
	else if (*lex->srci == '>' && *(lex->srci + 1) == '=')
		lex->srci += 2, lex->ipos.x += 2, lex->type = T_GREATEQ;
	else if (*lex->srci == '>')
		lex->srci++, lex->ipos.x++, lex->type = T_GREAT;

	/* math ops */
	else if (*lex->srci == '=')
		lex->srci++, lex->ipos.x++, lex->type = T_EQ;
	else if (*lex->srci == '+' && *(lex->srci + 1) == '=')
		lex->srci += 2, lex->ipos.x += 2, lex->type = T_PLUSEQ;
	else if (*lex->srci == '+')
		lex->srci++, lex->ipos.x++, lex->type = T_PLUS;
	else if (*lex->srci == '-' && *(lex->srci + 1) == '=')
		lex->srci += 2, lex->ipos.x += 2, lex->type = T_MINUSEQ;
	else if (*lex->srci == '-')
		lex->srci++, lex->ipos.x++, lex->type = T_MINUS;
	else if (*lex->srci == '*' && *(lex->srci + 1) == '*' && *(lex->srci + 1) == '=')
		lex->srci += 3, lex->ipos.x += 3, lex->type = T_DSTAREQ;
	else if (*lex->srci == '*' && *(lex->srci + 1) == '*')
		lex->srci += 2, lex->ipos.x += 2, lex->type = T_DSTAR;
	else if (*lex->srci == '*' && *(lex->srci + 1) == '=')
		lex->srci += 2, lex->ipos.x += 2, lex->type = T_STAREQ;
	else if (*lex->srci == '*')
		lex->srci++, lex->ipos.x++, lex->type = T_STAR;
	else if (*lex->srci == '/' && *(lex->srci + 1) == '/' && *(lex->srci + 1) == '=')
		lex->srci += 3, lex->ipos.x += 3, lex->type = T_DSLASHEQ;
	else if (*lex->srci == '/' && *(lex->srci + 1) == '/')
		lex->srci += 2, lex->ipos.x += 2, lex->type = T_DSLASH;
	else if (*lex->srci == '/' && *(lex->srci + 1) == '=')
		lex->srci += 2, lex->ipos.x += 2, lex->type = T_SLASHEQ;
	else if (*lex->srci == '/')
		lex->srci++, lex->ipos.x++, lex->type = T_SLASH;

	/* eof */
	else if (*lex->srci == '\0') {
		/* remaning dedents */
		if (lex->i_dep-- > 0)
			lex->type = T_DEDENT;
		else
			lex->type = T_EOF;
	}

	/* error */
	else
		lex->type = T_ERR,
		sprintf(lex->val, "Unexpected char '%c'", *lex->srci);
}