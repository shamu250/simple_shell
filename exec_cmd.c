#include "main.h"

/**
** exec_cmd - executes commands
** @se: Shell Environment struct
** Return: void
**/
void exec_cmd(shenv_t *se)
{
	(se->counter)++;
	if (se->linelen > 0)
	{
		switch (se->pid = fork())
		{
			case -1:
				perror("fork()");
			case 0: /* child */
				se->status = execve(se->cmd_tokens[0], se->cmd_tokens, NULL);
				/* if (_strlen(se->cmd_tokens[0]) > 0) */
				if (TRUE)
				{
					err_msg(se);
					perror("");
					exit(se->status);
				}
			default: /* parent */
				if (waitpid(se->pid, &(se->status), 0) < 0)
				{
					perror("waitpid()");
					exit(EXIT_FAILURE);
				}
		}
	}
	else if (is_interactive(STDIN_FILENO, se->buf))
		_puts("\n");
}

/**
** exec_abs_cmd - executes command with built token[0]
** @se: Shell Environmnet struct
** @arg0: string representing full_path of file to execute
** Return: void
**/
void exec_abs_cmd(shenv_t *se, char *arg0)
{
	(se->counter)++;
	if (se->linelen > 0)
	{
		switch (se->pid = fork())
		{
			case -1:
				perror("fork()");
			case 0: /* child */
				se->status = execve(arg0, se->cmd_tokens, NULL);
				/* printf("EAC-case0-arg0 = %s\n", arg0); */
				if (_strlen(arg0) > 0)
				{
					err_msg(se);
					perror("");
					exit(se->status);
				}
			default: /* parent */
				if (waitpid(se->pid, &(se->status), 0) < 0)
				{
					perror("waitpid()");
					exit(EXIT_FAILURE);
				}
		}
	}
	else if (is_interactive(STDIN_FILENO, se->buf))
		_puts("\n");
}
