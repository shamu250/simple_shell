#include "main.h"

/**
 * init_env - Initialize environment struct
 * @se: pointer to struct that holds vars for passing to functions
 **/

void init_env(shenv_t *se)
{
	/* se->pid = DUD */
	se->status = 0;
	se->linebuf = NULL;
	se->linelen = 0;
	se->linesize = 0;
	se->counter = 0;
	init_str_buffer(se->full_path, STR_BUF);
}


/**
 * init_cmd_tokens - wipe all contents of buffer to default value
 * @se: Shell Environment struct
 * Return: EXIT_SUCCESS
 **/
int init_cmd_tokens(shenv_t *se)
{
	int i;
	char *default_value = NULL;

	for (i = 0; i < BUFSIZE; i++)
	{
		/* printf("cmd_token[%d] = %p\n", i, se->cmd_tokens[i]); */
		se->cmd_tokens[i] = default_value;
	}
	return (EXIT_SUCCESS);
}

/**
 * init_path_tokens - wipe all contents of buffer to default value
 * @se: Shell Environment struct
 * Return: EXIT_SUCCESS
 **/
int init_path_tokens(shenv_t *se)
{
	int i;
	char *default_value = NULL;

	for (i = 0; i < BUFSIZE; i++)
	{
		/* printf("path_token[%d] = %p\n", i, se->path_tokens[i]); */
		se->path_tokens[i] = default_value;
		/* buffer[i] = NULL; */
	}
	return (EXIT_SUCCESS);
}

/**
 * free_all - frees all malloc'ed memory
 * @se: pointer to Shell Environment struct
 * Return: success on successful execution
 **/
int free_all(shenv_t *se)
{
	free(se->linebuf);
	free(se->path);
	return (EXIT_SUCCESS);
}

/**
 * init_str_buffer - wipe contents of a string buffer to null bytes
 * @buf: string buffer to be wiped
 * @bufsize: size of string buffer
 * Return: EXIT_SUCCESS on successful execution
 **/
int init_str_buffer(char *buf, int bufsize)
{
	int i;

	for (i = 0; i < bufsize; ++i)
		buf[i] = '\0';
	return (EXIT_SUCCESS);
}

