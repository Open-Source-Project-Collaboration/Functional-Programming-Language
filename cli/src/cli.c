#include "cli.h"


int main()
{
	compiler_main();
	vm_main();

	puts("Hello World from CLI!");
	return 0;
}