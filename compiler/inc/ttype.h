/*
 * This file containes the list of token types
 */

#ifndef FPL_COMPILER_TTYPE_H
#define FPL_COMPILER_TTYPE_H


/* list of tokens */
#define TTYPES\
	/* invincibles */\
	X(PENDING)\
	X(ERR)\
	X(EOF)\
	X(EOL)\
	X(INDENT)\
	X(DEDENT)\
	\
	/* literals */\
	X(NAME)\
	X(INT)\
	X(FLOAT)\
	X(STR)\
	X(BOOL)\
	X(ARRAY)\
	\
	/* keywords */\
	X(LET)\
	X(FOR)\
	X(WHILE)\
	X(MUT)\
	X(MOD)\
	X(USE)\
	X(TYPE)\
	X(MATCH)\
	\
	/* punctuation */\
	X(COLON)\
	X(DOT)\
	X(LPAR)\
	X(RPAR)\
	X(LBRAC)\
	X(RBRAC)\
	X(SEMI)\
	X(BAR)\
	X(PIPE)\
	X(ARROW)\
	\
	/* logic ops */\
	X(IN)\
	X(NOT)\
	X(DEQ)\
	X(NOTEQ)\
	X(AND)\
	X(OR)\
	X(LESS)\
	X(LESSEQ)\
	X(GREAT)\
	X(GREATEQ)\
	\
	/* math ops */\
	X(EQ)\
	X(PLUS)\
	X(PLUSEQ)\
	X(MINUS)\
	X(MINUSEQ)\
	X(STAR)\
	X(STAREQ)\
	X(DSTAR)\
	X(DSTAREQ)\
	X(SLASH)\
	X(SLASHEQ)\
	X(DSLASH)\
	X(DSLASHEQ)\
	\
	/* ast misc */\
	X(STMT)\
	\
	X(LAST)


/* convert to enum */
typedef enum {
	#define X(t) T_##t,
		TTYPES
	#undef X
} ttype_t;


/* convert to string */
static const char *ttype_str[] = {
	#define X(t) #t,
		TTYPES
	#undef X
};


#endif