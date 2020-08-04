# General stuff
statements <- statements statement
            | statement statement
	    | statement

statement <- comment
           | fcall
	   | def
	   | if
	   | for
	   | while
	   | mod
	   | use
	   | type
	   | match
	   | 'empty'

comment <- r'#.*\n'


# Matching
match <- 'match' expr ':' matchbody

matchbody <- INDENT match_statements DEDENT

match_statements <- match_statements match_statement
                  | match_statement match_statement
		  | match_statement

match_statement <- NAME '=>' defbody


# Type definitions
type <- 'type' NAME '=' [enum_or_struct]

enum <- enum '|' NAME
      | NAME '|' NAME
      | NAME

struct <- INDENT structdefs DEDENT

structdefs <- structdefs structdef
            | structdef structdef
	    | structdef

structdef <- NAME ':' TYPE
           | 'empty'

enum_or_struct <- enum
                | struct


# Importing modules
mod <- 'mod' NAME
use <- 'use' dotop


# Loops
for <- 'for' NAME 'in' lval ':' defbody
while <- 'while' condition ':' defbody


# Conditional flow
if <- 'if' condition ':' block [elif_or_else]

elif <- 'elif' condition ':' block [elif_or_else]

else <- 'else' ':' block

elif_or_else <- elif
              | else

condition <- condition LOGIC_OP condition
           | condition CMP_OP expr
           | expr CMP_OP expr


# Function/variable definitions
def <- 'let' ['mut'] NAME ['<' NAME '>'] [defargs] '=' defbody

defargs <- defargs defarg
          | defarg defarg
	  | defarg

defarg <- NAME [':' TYPE]

defbody <- pipe
         | block

pipe <- pipe '|>' expr
      | expr '|>' expr
      | expr

block <- INDENT statemets DEDENT


# Function calls
fcall <- dotop [args]
       | dotop '(' [args] ')'

args <- args arg
      | arg arg
      | arg

arg <- '(' pipe ')'
     | primitive


# Dot operator
dotop <- dotop '.' NAME
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
       | '[' pipe ']'

tuple <- tuple ';' pipe
       | pipe ';' pipe

literal <- fcall
         | primitive

primitive <- NAME
           | INT
	   | FLOAT
	   | STR
	   | BOOL
	   | array