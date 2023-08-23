#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include "shell.h"
/**
 * main - Shell Program
 * @ac: count of input parameters to program
 * @av: parameters as input to program
 * @env: unix environment
 *
 * Return: Should only exit through shell inputs
 */
int main(int ac, char **av, char **env)
{
	size_t bsize = 0;
	char **comd, *pCmd, *bfr = NULL;
	hshpack *sck;
	int errnn = 0, exnumm = 0, r = 0, runAble = 0, sEnv, enull = 0;
	ssize_t isBuiltIned;

	if (ac > 1 || av == NULL)
		write(2, "Please run with no arguments\n", 29), exit(127);
	signal(SIGINT, signal_handler);
	sEnv = _strlendp(env);
	env = _copydoublep(env, sEnv, sEnv);
	sck = set_struct(av[0], &errnn, &exnumm, &r, &runAble, &env, &enull);
	while (1)
	{
		comd = NULL;
		comd = checkInput(ac, av, &bsize, &bfr, sck);
		if (!comd)
			continue;
		addCmd(sck, bfr, comd[0], comd);
		isBuiltIned = built_ints(sck);
		if (isBuiltIned == -1 || isBuiltIned == 1)
			continue;
		pCmd = _path(comd[0], env, sck);
		addPathToCmd(sck, pCmd);
		if (!pCmd)
		{
			free(comd);
			sck->errnum[0] += 1, _error(0, sck, 127);
			continue;
		}
		else if (access(pCmd, X_OK) == -1)
			_error(1, sck, 126);
		else
			executeCmd(pCmd, comd, env, sck);
		free(comd);
		free(pCmd);

	}
	free_doubpoint(*(sck->envCpy)), free(sck);
	return (0);
}
/**
 * set_struct - initializes shell struct
 * @argv0: name of executable
 * @errn: number of error message
 * @exnum: exit number of shell
 * @relation: relation for logical operators
 * @run_able: if cmd should be run
 * @env: current environment
 * @unsetnull: check for setting environment to NULL
 *
 * Return: Pointer to struct
 *
 */
hshpack *set_struct(char *argv0, int *errn, int *exnum,
		    int *r, int *runAble, char ***e, int *unsetnul)
{
	hshpack *spack;

	spack = malloc(sizeof(struct Hshpack));
	if (spack == 0)
		return (write(2, "Memory Error", 22), NULL);
	spack->hshname = argv0;
	spack->bfr = NULL;
	spack->cmd = NULL;
	spack->options = NULL;
	spack->path = NULL;
	spack->errnum = errn;
	spack->exitnum = exnum;
	spack->relation = r;
	spack->run_able = runAble;
	spack->envCpy = e;
	spack->unsetnull = unsetnul;

	return (spack);
}
/**
 * addCmd - adds values to shell struct
 * @shpack: shell struct
 * @buffer: string written after prompt
 * @command: command written after prompt
 * @parameters: parameters of command
 *
 * Return: No return
 */
void addCmd(hshpack *shpack, char *buffer, char *command, char **parameters)
{
	shpack->bfr = buffer;
	shpack->cmd = command;
	shpack->options = parameters;
}

/**
 * addPathToCmd - initializes path value of struct
 * @shpack: shell struct
 * @pathCmd: path of cmd written after propmpt
 *
 * Return: No Return
 */
void addPathToCmd(hshpack *shpack, char *pathCmd)
{
	shpack->path = pathCmd;
}
