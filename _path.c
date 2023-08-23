#include "shell.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * _pathcheck - check if current dir must be added
 * @pth: path env variable
 *
 * Return: Pointer to adress of new PATH
 *
 */

char *_pathcheck(char *pth)
{
	char *npth;
	int n, j, nsize, c = 0;

	for (n = 0; pth[n]; n++)
	{

		if (pth[n] == '=' && pth[n + 1] == ':')
			c++;
		if (pth[n] == ':' && pth[n + 1] == ':')
			c++;
		if (pth[n] == ':' && pth[n + 1] == '\0')
			c++;
	}
	if (c == 0)
		return (0);
	nsize = _strlen(pth) + 1 + c;
	npth = malloc(sizeof(char) * nsize);

	for (n = 0, j = 0; n < nsize; n++, j++)
	{
		if (pth[j] == '=' && pth[j + 1] == ':')
		{
			npth[n] = pth[j], npth[n + 1] = '.', n++;
			continue;
		}
		if (pth[j] == ':' && pth[j + 1] == ':')
		{
			npth[n] = pth[j], npth[n + 1] = '.', n++;
			continue;
		}
		if (pth[j] == ':' && pth[j + 1] == '\0')
		{
			npth[n] = pth[j], npth[n + 1] = '.', n++;
			continue;
		}
		npth[n] = pth[j];
	}
	free(pth);
	return (npth);
}
/**
 * _path - Searches for a cmd in PATH
 * @cmd: string contating env variable PATH
 * @env: current environment
 * @shpack: struct containing shell info
 *
 * Return: Pointer to adress of cmd in PATH or by itself
 *
 */

char *_path(char *cmd, char **env, hshpack *shpack)
{
	char *p1, *p2;
	struct stat s;
	char *t, *ct, *c2, *pathcheck, *d = ":=";
	int i;

	for (i = 0; cmd[i]; i++)
		if (cmd[i] == '/')
		{
			if (stat(cmd, &s) == 0)
				return (ct = str_concat(cmd, '\0'));
			else
				return (0);
		}

	p2 = _getenv("PATH", env);
	(void) shpack;
	if (!p2)
		return (0);
	p1 = _strdup(p2);
	pathcheck = _pathcheck(p1);
	if (pathcheck)
		p1 = pathcheck;
	t = _strtok(p1, d);
	for (t = _strtok(0, d); t; t = _strtok(0, d))
	{
		ct = str_concat(t, "/");
		c2 = str_concat(ct, cmd);
		free(ct);
		if (stat(c2, &s) == 0)
		{
			free(p1);
			return (c2);
		}
		free(c2);
	}

	free(p1);
	return (0);
}
