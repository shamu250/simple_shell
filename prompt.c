#include "main.h"
/**
**prompt - interactive or non interactive
**@fd: stream
**@buff: buffer
**Return: void
**/
void prompt(int fd, struct stat buff)
{
	fstat(fd, &buff);

	if (is_interactive(fd, buff))
		_puts(PROMPT);
}

/**
 *_puts - put string to stdout
 *@str: string to send to stdout
**/
void _puts(char *str)
{
	unsigned int len;

	len = _strlen(str);

	write(STDOUT_FILENO, str, len);

}


/**
 *_puts_err - output string to stderr
 *@str: string to send to stderr
**/
void _puts_err(char *str)
{
	unsigned int len;

	len = _strlen(str);

	write(STDERR_FILENO, str, len);

}

/**
** is_interactive - returns a "boolean" indicating wheather stream
**         (typically STDIN_FILENO) is interactive or not
**         NOTE: no guarantees on results if fd is not an input stream in
**         general or STDIN_FILENO in particular
** @fd: file descriptor
** @buff: buffer
** Return: int
**/
int is_interactive(int fd, struct stat buff)
{
	fstat(fd, &buff);

	if (!(S_ISCHR(buff.st_mode)))
		return (FALSE);

	else
		return (TRUE);
}

