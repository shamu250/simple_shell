#include "main.h"
/**
 * copy_into_strbuf - copies a string into a buffer of specified size
 * @buf: buffer to write into
 * @bufsize: size of buffer
 * @src: source string to copy from
 * Return: EXIT_SUCCESS on success, or EXIT_FAILURE otherwise
 **/
int copy_into_strbuf(char buf[], int bufsize, char *src)
{
	int i;

	i = 0;

	if (bufsize <= 0 || !src)
		return (EXIT_FAILURE);

	while (i < bufsize && src[i])
	{
		buf[i] = src[i];
		i++;
	}

	if (i == bufsize && src[i])
	{
		perror("copy_into_strbuf: buffer_overflow");
	}
	else
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

