#include "helpers.h"


char *ftos(char *fpath)
{
	FILE *fp = fopen(fpath, "r");
	if (fp == NULL)
		return NULL;

	fseek(fp, 0, SEEK_END);
	const size_t size = ftell(fp);
	rewind(fp);

	char *src = malloc(size + 1);
	fread(src, 1, size, fp);

	fclose(fp);
	return src;
}


char *strdup(char *s)
{
	if (s == NULL)
		return NULL;

	const size_t size = strlen(s);
	return strcpy(malloc(size + 1), s);
}