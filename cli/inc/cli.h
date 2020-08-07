#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"
#include "vm.h"


/* cli commands list */
int cli_unknown(char *cmd);
int cli_help();
int cli_lex_$file(char *fpath);
int cli_parse_$file(char *fpath);