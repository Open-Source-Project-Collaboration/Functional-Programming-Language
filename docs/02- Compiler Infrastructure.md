# 02 - Compiler Infrastructure

Firstly, get your input:

``` C
char *src = ftos(/* filepath */);
if (src == NULL) {
	puts("Can not open file");
	exit(EXIT_FAILURE);
}
```

## Lexing

You can create a lexer using the source

``` C
lex_t lexer = new_lex(src);
```

You can print out all the tokens if want like this:

``` C
while (lexer.type != T_ERR && lexer.type != T_EOF) {
	lex_print(&lexer);
	lex_next(&lexer);
}

/* don't forget to free */
free_lex(&lexer);
```

> In fact, this is what new_parser(char *src) does internally


## Parsing (LALR(1))

You can create a parser using the source

``` C
parser_t parser = new_parser(src);
```

Upon initialization, it parses the src.
You can print the AST like this:

``` C
parser_print(&parser);

/* don't forget to free */
free_parser(&parser);
```

> If it didn't generate AST correctly, don't worry, no errors here. Later on checks will catch that definitly


## Checking the AST

In order to catch errors in the parsing stage, you have to pass ast through
a couple of checking functions.

All of them check different stuff, but overall
they make sure no errors are present.

A simple introduction would be:

``` C
ast_check_toplevel(&parser.ast);

/* check to see generated errors */
if (parser.error)
	parser_printerr(&parser);
```

One can also don't mind doing checks by hand, and instead check ast automatically
using this:

``` C
ast_check_all(&parser.ast);

if (parser.error)
	parser_printerr(&parser));
```

`ast_check_all(node_t *ast)` passes ast in the proper order to every check.



# Optimizing

Likewise checking, optimizing stage also has multiple passes.
But you can always use `ast_optimize_all(node_t *ast)`.


## Compiling

This is the easiest part. Hence all the code compiles into a single opcode array,
all you have to do is.

``` C
program_t program = compile(&parser.ast);

/* you can then write that to a file */
program_write(&program, "filepath.fpl");

/* or just run it directly */
int ret = program_run(&program);
return ret;
```


## Virtual Machine

You can run the compiled code using:

``` C
vm_run(program.ops);
```