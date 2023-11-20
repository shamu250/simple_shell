#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

#define UNUSED(x) (void)(x)
#define PROMPT "$ "
#define BUFSIZE 1024
#define STR_BUF 1024
#define TRUE 1
#define FALSE 0
#define DELIM "\t\r\n "

/*macros for error switch*/
#define ERROR_MALLOC "Unable to malloc space\n"
#define ERROR_FORK "Unable to fork and create child process\n"
#define ERROR_PATH "No such file or directory\n"

extern char **environ;

/**
 * struct shenv - shell environment variables
 * @pid: process id
 * @linebuf: obtained by getline
 * @av: argv passed into main (copy or original?)
 * @cmd_tokens: this will contain array of strings, like *argv[]
 * @path: a copy of path from environ or envp
 * @path_tokens: array of pointers to tokens in path
 * @full_path: concat of path, slash, and executable file
 * @linelen: line length return val of getline
 * @linesize: receives allocated size from getline
 * @status: status to exit with
 * @counter: number of lines executed by shell (returned on exit??)
 * @buf: exists to pass to pass to fstat
 **/

typedef struct shenv
{
	pid_t pid;
	char *linebuf;
	char **av;
	char *cmd_tokens[BUFSIZE];
	char path[STR_BUF];
	char *path_tokens[BUFSIZE];
	char full_path[STR_BUF];
	ssize_t linelen;
	size_t linesize;
	/* char *my_argv[2]; */
	int status;
	int counter;

	struct stat buf;
	} shenv_t;

/**
 * struct built_s - struct for names of built in funcs  & func pointers
 * @name: name of function as called from shell command line
 * @p: pointer to function associated with name
 **/
typedef struct built_s
{
	char *name;
	int (*p)(shenv_t *);

} built_t;

/* built_ins.c */
int execute_builtin(shenv_t *se);
int built_exit(shenv_t *se);
int built_p_env(shenv_t *se);
int number_builtins(built_t built_in[]);

/* hsh.c -- main */
int absolute_path(shenv_t *se);

/* exec_cmd.c */
void exec_cmd(shenv_t *se);
void exec_abs_cmd(shenv_t *se, char *arv0);
void err_msg(shenv_t *se);

/* helper1.c */
int _strcmp(char *s1, char *s2);
int str_eval(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
int _strlen(char *s);
void print_argv(char **argv);

/* helper2.c */
char *_strdup(char *str);
char *str_concat(char *s1, char *s2);
int init_char_buffer(char *buffer, int bufsize);
int init_Cptr_buffer(char **buffer, int bufsize);
void tokenize(shenv_t *se);

/* error_switch.c */
void errors(char error_msg);

/* init_free.c */
void init_env(shenv_t *shell_env);
int init_cmd_tokens(shenv_t *se);
int init_path_tokens(shenv_t *se);
int free_all(shenv_t *se);
int init_str_buffer(char *buf, int bufsize);

/* math_helper.c */
int itoa(int n, char s[]);
int _abs(int n);

/* path_helper.c */
char *get_EV(char *var);
void build_path_array(shenv_t *se);
int get_path(shenv_t *se);

/* prompt.c */
void prompt(int fd, struct stat buff);
void _puts(char *str);
void _puts_err(char *str);
int is_interactive(int fd, struct stat buff);

/* helper3.c */
int copy_into_strbuf(char buf[], int bufsize, char *src);

#endif /* MAIN_H */

