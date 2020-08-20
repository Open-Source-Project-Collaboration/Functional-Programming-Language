#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"
#include "vm.h"
#include "helpers.h"


/* cli commands list */
int cli_unknown(char *cmd);
int cli_help();
int cli_parse_$file(char *fpath);