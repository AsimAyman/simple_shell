#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include "shell.h"

/**
 * executeCmd - creates a child process to execute a cmd
 *
 * @prog: command that will be executed
 * @cmd: arguments of command
 * @e: current environment
 * @sck: struct with shell information
 *
 * Return: pointer to the value in the environment,
 * or NULL if there is no match
 *
 */
int executeCmd(char *prog, char *cmd[], char **e, hshpack *sck)
{
	pid_t p, s;
	int e = 0, w = 0;

	p = fork();
	signal(SIGINT, signal_handler2);
	if (p == -1)
	{
		write(2, "Fork Error", 10);
		exit(-1);
	}
	if (p == 0)
	{

		e = execve(prog, cmd, e);
		if (e == -1)
		{
			_exit(-1);
		}
	}
	else
	{
		w = wait(&s);
		signal(SIGINT, signal_handler);
		if (w == -1)
			exit(-1);
		if (WEXITSTATUS(s) == 0)
			sck->exitnum[0] = 0;
		else
			sck->exitnum[0] = 2;
	}

	sck->errnum[0] += 1;
	return (0);
}
