#include "main.h"

/**
**_getline - get user input
** @fp: buffer
** Return: input
**/

char *_getline(FILE *fp)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read = getline(&line, &len, fp);

	if (read  == -1)
	{
		free(line);
		exit(EXIT_SUCCESS);
	}
	return (line);
}

