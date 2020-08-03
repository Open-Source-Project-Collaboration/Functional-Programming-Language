# General stuff
statements <- statements statement
            | statement statement
	    | statement

statement <- comment
           | fcall
	   | def

comment <- r'#.*\n'


# Function/variable definitions
def <- 'let' ['mut'] NAME [defargs] '=' defbody

defargs <- defargs defarg
          | defarg defarg
	  | defarg

defarg <- NAME [':' TYPE]

defbody <- lval
         | block

lval <- fcall
      | expr

block <- INDENT statemets DEDENT


# Function calls
fcall <- rval args
       | rval '(' args ')'

args <- args arg
      | arg arg
      | arg

arg <- '(' lval ')'
     | literal


# Dot operator
rval <- dotop '.' NAME
       | NAME '.' NAME
       | NAME


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