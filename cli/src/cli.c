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

	puts("\thelp          -> prints this message");
	puts("\t(more will come)\n");

	return EXIT_SUCCESS;
}