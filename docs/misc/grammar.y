# General stuff
statements <- statements statement
            | statement statement
	    | statement

statement <- comment
           | fcall
	   | vardef

comment <- r'#.*\n'


# Variables
vardef <- im_vardef
        | mut_vardef

im_vardef <- 'let' NAME [':' TYPE] ['=' lval]
mut_vardef <- 'let' 'mut' NAME [':' TYPE] ['=' lval]

lval <- fcall
      | expr


# Function calls
fcall <- NAME args

args <- args literal
      | literal literal
      | literal


# Math
expr <- term '+' expr
      | term '-' expr
      | term

term <- fact '*' term
      | fact '/' term
      | fact

fact <- '(' expr ')'
      | literal


# Primitives
array <- '[' tuple ']'
       | '[' lval ']'

tuple <- tuple ';' lval
       | lval ';' lval

literal <- NAME
         | INT
	 | FLOAT
	 | STR
	 | BOOL
	 | array