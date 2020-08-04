#include "cli.h"


int main(int argc, char **argv)
{
	/* check args */
	if (argc == 1)
		return cli_help();

	/* get the command */
	const char *cmd = argv[1];

	/* check the command */
	if (strcmp(cmd, "help") == 0)
		return cli_help();
	else if (strcmp(cmd, "lex") == 0)
		return cli_lex_$file(argv[2]);

	return cli_unknown(argv[2]);
}


int cli_unknown(char *cmd)
{
	printf("Unknown command '%s'\n", cmd);
	puts("Please type 'fpl help' to see the options");
	return EXIT_FAILURE;
}


int cli_help()
{
	puts("List of commands:");

	puts("help          -> prints this message");
	puts("lex <file>    -> prints the tokens");
	puts("(more will come)");

	return EXIT_SUCCESS;
}


int cli_lex_$file(char *fpath)
{
	char *src = ftos(fpath);
	if (src == NULL) {
		printf("ERROR: Failed to open file '%s'\n", fpath);
		return EXIT_FAILURE;
	}

	puts(src);

	free(src);
	return EXIT_SUCCESS;
}