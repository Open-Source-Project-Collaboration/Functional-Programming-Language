#include "cli.h"


int main(int argc, char **argv)
{
	/* check args */
	if (argc == 1)
		return cli_help();

	/* get the command */
	char *cmd = argv[1];

	/* check the command */
	if (strcmp(cmd, "help") == 0)
		return cli_help();
	else if (strcmp(cmd, "parse") == 0)
		return cli_parse_$file(argv[2]);

	return cli_unknown(cmd);
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

	puts("\thelp          -> prints this message");
	puts("\t(more will come)\n");

	return EXIT_SUCCESS;
}


int cli_parse_$file(char *fpath)
{
	char *src = ftos(fpath);
	if (src == NULL) {
		puts("Failed to open file");
		return EXIT_FAILURE;
	}

	node_t *stmts = parse(src);
	print_node(stmts);

	free_node(stmts);
	free(src);
	return EXIT_SUCCESS;
}