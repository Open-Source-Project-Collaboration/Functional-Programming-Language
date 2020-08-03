# General stuff
statements <- statements statement
            | statement statement
	    | statement

statement <- comment
           | fcall
	   | def
	   | if

comment <- r'#.*\n'


# Conditional flow
if <- 'if' condition ':' block [elif_or_else]

elif <- 'elif' condition ':' block [elif_or_else]

else <- 'else' ':' block

elif_or_else <- elif
              | else

condition <- condition LOGIC_OP condition
           | condition CMP_OP lval
           | lval CMP_OP lval
	   | lval


# Function/variable definitions
def <- 'let' ['mut'] NAME [defargs] '=' defbody

defargs <- defargs defarg
          | defarg defarg
	  | defarg

defarg <- NAME [':' TYPE]

defbody <- pipe
         | block

pipe <- pipe '|>' lval
      | lval '|>' lval
      | lval

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