#include "main.h"

/**
 * _strdup - duplicate a string and place it in newly allocated space in
 *          memory
 * @str: string to be copied
 * Return: pointer to duplicated string, or NULL if sufficient memory
 *         is not available
 */
char *_strdup(char *str)
{
	char *new;
	unsigned int i, size;

	if (str == NULL)
		return (NULL);

	size = _strlen(str) + 1;
	new = malloc(size * sizeof(char));
	for (i = 0; str[i] != '\0'; i++)
		new[i] = str[i];

	new[size - 1] = '\0';
	return (new);
}

/**
 * str_concat - concatenates two string
 * @s1: first string to be concatenated NULL is considered to be empty string`
 * @s2: second string to be concatenated
 * Return: newly allocated memory with concatenated string
 *           NULL is returned on failure
 */
char *str_concat(char *s1, char *s2)
{
	unsigned int i, len1, len2, newlen;
	char *new;

	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";
	for (len1 = 0; s1[len1]; len1++)
		;
	for (len2 = 0; s2[len2]; len2++)
		;
	newlen = len1 + len2;
	new = malloc((newlen + 1) * sizeof(char));
	for (i = 0; s1[i] != '\0'; i++)
		new[i] = s1[i];
	for (i = 0; s2[i] != '\0'; i++)
		new[len1 + i] = s2[i];
	new[newlen] = '\0';
	return (new);
}

/**
 * init_char_buffer - wipe all contents of buffer to default value
 * @buffer: buffer to be initialized
 * @bufsize: size of buffer to be wiped/initialized
 * Return: EXIT_SUCCESS
 **/
int init_char_buffer(char *buffer, int bufsize)
{
	int i;
	const char default_char = '\0';

	for (i = 0; i < bufsize; i++)
		buffer[i] = default_char;
	return (EXIT_SUCCESS);
}

/**
 * init_Cptr_buffer - wipe all contents of buffer to default value
 * @buffer: buffer to be initialized
 * @bufsize: size of buffer to be wiped/initialized
 * Return: EXIT_SUCCESS
 **/
int init_Cptr_buffer(char **buffer, int bufsize)
{
	int i;
	/* char *default_value = NULL; */

	for (i = 0; i < bufsize; i++)
	{
		/* printf("Cptr[%d] = %p\n", i, buffer[i]); */
		/* buffer[i] = default_value; */
		buffer[i] = NULL;
	}
	return (EXIT_SUCCESS);
}
/**
 * tokenize - accepts string from getline, creates null-terminated token array
 *            token array stored here: se->cmd_tokens[]
 * @se: shell env struct that contains many things, including:
 *      se.linebuf (contains string from getline)
 *      se.cmd_tokens (the array of tokens, which we are building here
 *       this function "returns" a shellenv struct that contains a modified
 *       cmd_tokens element formatted to null-terminated *argv[] format
 **/
void tokenize(shenv_t *se)
{
	char *token;
	unsigned int i = 1;

	token = se->cmd_tokens[0] = strtok(se->linebuf, DELIM);
	while (i < BUFSIZE && token && token[0])
	{
		token = se->cmd_tokens[i] = strtok(NULL, DELIM);
		if (!token)
			break;
		/* printf("token#[%d] %p\n", i, token); */
		/* printf("se->cmd_tokens[%d] %p\n", i, se->cmd_tokens[i]); */
		i++;
	}
	if (i >= BUFSIZE)
	{
		se->cmd_tokens[BUFSIZE - 1] = NULL;
		/* TODO: return an error: buffer overflow */
	}
	else
		se->cmd_tokens[i] = NULL;
}

