#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>

/**
 * struct Hshpack - struct containing important shell info
 * @hshname: name of the shell (argv[0])
 * @buffer: full buffer written in prompt
 * @cmd: command written after prompt
 * @options: options of the command
 * @path: path of the cmd if found, else cmd itself
 * @errnum: error count
 * @exitnum: number of exit that the shell will have
 * @relation: true or false for logical operators
 * @run_able: check for running or not a command
 * @next: singly list link
 * @envCpy: copy of environment
 * @unsetnull: check for setting environment to NULL
 *
 * Description: Struct containing important shell info
 *
 */
typedef struct Hshpack
{
	char *hshname;        /* Name of shell argv[0] */
	char *bfr;         /* complete line written in prompt */
	char *cmd;            /* current command */
	char **options;       /* options of current command */
	char *path;           /* absolute path of command */
	int *errnum;          /* error number for message */
	int *exitnum;         /* exit number */
	int *relation;        /* 0 Undef, 1 ||, 2 && */
	int *run_able;        /* 0 False 1 True (Is able to run)*/
	struct Hshpack *next; /*adress of next cmd to run */
	char ***envCpy;       /* current environment */
	int *unsetnull;       /*check for setting environment to NULL */

} hshpack;

/**
 * struct b_ins - struct for built ins
 * @cmd: built in
 * @f: function of built in
 *
 * Description: Struct for calling built in functions
 *
 */
typedef struct b_ins
{
	char *cmd;
	ssize_t (*f)(hshpack *shpack);
} b_ins;

/**
 * struct Helps - struct for built ins
 * @built: built in command
 * @h: help function of built in
 *
 * Description: Struct for calling built in functions
 *
 */
typedef struct Helps
{
	char *built;
	void (*h)(void);
} helps;




char *_getenv(const char *name, char **env);
char *_path(char *cmd, char **env, hshpack *shpack);
char *_strdup(char *s);
char *str_concat(char *ss1, char *ss2);
int _strlen(char *s);
char *_strcpy(char *st1, char *st2);
char *_strtok(char *s, const char *d);
char **getParameters(char *rBuffer, hshpack *sck);
int executeCmd(char *prog, char *cmd[], char **e, hshpack  *sck);
void signal_handler(int xc);
void signal_handler2(int xc);
int _getline(char **buffer, size_t *bufsize, int fd);
void free_doubpoint(char **pp);
int _strlendp(char **s);
char **checkInput(int ac, char **av, size_t *bsize),
char **buffer, hshpack *sck);
hshpack *set_struct(char *argv0, int *errn, int *exnum, int *relation,
		    int *run_able, char ***env, int *unsetnull);
int _error(int errn, hshpack *shpack, int exnum);
void addCmd(hshpack *shpack, char *buffer, char *command, char **parameters);
void addPathToCmd(hshpack *shpack, char *pathCmd);
ssize_t built_ints(hshpack *sck);
ssize_t _exit_cmd(hshpack *sck);
int _strcmp(char *s1, char *s2);
long _atoi(char *sc);
long _pow(long b, long p);
char **_copydoublep(char **pp, int osize, int nsize);
int _strlendp(char **ss);
char **_setenv(char **env, char *var, char *val, hshpack *sck);
char **_unsetenv(char **env, char *variable, hshpack *shpack);
int _isdigit(int cc);
int _isnumber(char *st);
ssize_t _cd_cmd(hshpack *sck);
char *deleteComment(char *s);


ssize_t _help_cmd(hshpack *sck);
void _puts(char *z);
void help_unsetenv(void);
void help_cd(void);
void help_help(void);
void help_alias(void);
void printsHelp(void);

#endif
