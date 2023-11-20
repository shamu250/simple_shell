#include "main.h"

/**
**execute_builtin -  executes builtins listed in struct
** @se: shell env struct
**Return: success if builtin runs otherwise, failure code
**/

int execute_builtin(shenv_t *se)
{
	built_t built_in[] = {
	{"exit", built_exit},
	{"env", built_p_env},
	{NULL, NULL},
	};
	int status;
	int i;

	if (se->cmd_tokens == NULL || se->cmd_tokens[0] == NULL)
		return (1);

	for (i = 0; i < number_builtins(built_in); i++)
	{
		if (_strcmp(se->cmd_tokens[0], built_in[i].name) == 0)
		{
			status = built_in[i].p(se);
			return (status);
		}
	}
	return (EXIT_FAILURE);
}
/**
** number_builtins -  return number of built-in commands
** @built_in: array associating strings with pointers to functions
** Return: number of built-ins
**/
int number_builtins(built_t built_in[])
{

	int i = 0;

	while (built_in[i].name != NULL)
		i++;
	return (i);
}

