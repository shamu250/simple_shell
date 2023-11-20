#include "main.h"

/**
 * get_EV - get specified Environ Variable from environ
 * @var: variable name to search for in Environment Variables
 * Return: malloc'ed duplicate of env_var, or NULL if no match
 **/
char *get_EV(char *var)
{
	int i = 0;

	while (environ[i])
	{
		if (str_eval(environ[i], var) >= _strlen(var))
		{
			/* printf("getEV-> %s\n", environ[i]); */
			return (_strdup(environ[i]));
		}
		i++;
	}
	return (NULL);
}

/**
 * build_path_array - build array of paths in se->path_tokens using $PATH
 * @se: pointer to shell environment variable
 **/

void build_path_array(shenv_t *se)
{
	int i;
	char *tmp, *tmp_path;

	init_path_tokens(se);
	init_char_buffer(se->path, STR_BUF);
	/* se->path = get_EV("PATH"); */
	tmp_path = get_EV("PATH");
	copy_into_strbuf(se->path, STR_BUF, tmp_path);
	free(tmp_path);
	tmp = strtok(se->path, "=");
	for (i = 0; tmp; i++)
	{
		se->path_tokens[i] = tmp = strtok(NULL, ":");
	}
}

/**
 * get_path - returns executable path, or NULL if none exists
 * @se: Shell Evironment struct
 * Return: EXIT_SUCCESS = se->full_path contains legit path
 * Note: this does not implement the -a flag which would
 *       list all instances on the whole path
 */
int get_path(shenv_t *se)
{
	unsigned int i = 0;
	struct stat st;
	char *tmp, *path_slash;

	build_path_array(se);
	/* while (se->path_tokens[i]) */
	if (se->cmd_tokens[0])
	{
		i = 0;
		while (se->path_tokens[i])
		{
			path_slash = str_concat(se->path_tokens[i], "/");
			tmp = str_concat(path_slash, se->cmd_tokens[0]);
			/* printf("tmp-concat[%d]len[%d] = %s\n", i, _strlen(tmp), tmp); */
			if (_strlen(tmp) < STR_BUF)
			{
				_strcpy(se->full_path, tmp);
				/* printf("full_path = %s\n", se->full_path); */
			}
			else
			{ /* TODO: integrate with error code functions */
				perror("STR_BUF overflow .. averted");
				_exit(-1); /* not sure of proper status to pass here */
			}
			free(path_slash);
			free(tmp);
			if (stat(se->full_path, &st) == 0)
				return (EXIT_SUCCESS);
			/* free(se->full_path); */
			i++;
		}
		/* free(full_path); */
	}
	else
		_puts_err("get_path --> unexpected error");
	/* free(path); */
	return (EXIT_FAILURE);
}

