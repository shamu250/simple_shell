#include "main.h"
/**
** errors - writes error depending on the case letter
** @error_msg: error letter that goes with perror message
** Return: void
**/

void errors(char error_msg)
{

   /* local variable definition */

	switch (error_msg)
	{
	case 'A':
		write(STDERR_FILENO, ERROR_FORK, _strlen(ERROR_FORK));
		perror("Error");
		break;

	case 'B':
		perror("Error");
		break;

	case 'C':
		write(STDERR_FILENO, ERROR_MALLOC, _strlen(ERROR_FORK));
		break;


	case 'D':
		write(STDERR_FILENO, ERROR_PATH, _strlen(ERROR_PATH));
		break;

	default:
		return;
	}

}

/**
 * err_msg - print prepend error msg to stderr
 * @se: shell environment struct
 **/

void err_msg(shenv_t *se)
{
	char alpha_counter[30];
	int i;

	for (i = 0; i < 30; i++)
		alpha_counter[i] = '\0';

	_puts_err("hsh: ");
	itoa(se->counter, alpha_counter);
	_puts_err(alpha_counter);
	_puts_err(": ");
	_puts_err(se->cmd_tokens[0]);
}

