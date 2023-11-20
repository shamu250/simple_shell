#include "main.h"

/**
 * absolute_path - returns boolean indicating if path-string
 *                 starts with '/', thus being an absolute path
 * @se: pointer to shell environment struct
 * Return: 1 if TRUE, 0 if FALSE, -1 if ERROR
 **/

int absolute_path(shenv_t *se)
{
	if (se->cmd_tokens && se->cmd_tokens[0])
	{
		if (se->cmd_tokens[0][0] == '/')
			return (TRUE);
		else
			return (FALSE);
	}
	else
		return (-1);
}

/**
 * main - simple shell, modelled after /bin/sh
 * @ac: number of passed in args
 * @av: array of args (strings) passed into main
 * Return: -1 on getline error, else # of commands executed by shell
 **/

int main(int ac, char **av)
{
	/* char *my_argv[2]; */
	shenv_t se;
	int not_builtin, is_abs_path;


	UNUSED(ac);
	UNUSED(av);
	init_env(&se);
	do {
		prompt(STDIN_FILENO, se.buf);
		se.linelen = getline(&(se.linebuf), &(se.linesize), stdin);
		tokenize(&se);
		not_builtin = execute_builtin(&se);
		if (not_builtin)
		{
			/* printf("not_builtin\n"); */
			is_abs_path = absolute_path(&se);
			if (is_abs_path)
			{
				/* printf("is_abs_path = %d\n", is_abs_path); */
				exec_cmd(&se);
			}
			else
			{
				/* printf("not absolute path\n"); */
				get_path(&se); /* not using return status of get_path() */
				{
					/* printf("woo hoo!!! I wanna execute this:\n"); */
					exec_abs_cmd(&se, se.full_path);
				}
			}
		}
	} while (se.linelen > 0);
	/* printf("linelen = %lu\n", linelen); */
	free(se.linebuf);
	se.linebuf = NULL;
	if (se.linelen == -1)
		return (-1);
	else
		return (se.counter);
}

