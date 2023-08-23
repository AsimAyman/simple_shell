#include <limits.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "shell.h"

/**
 * auxcd2 - auxiliary function of cd built in
 * @sck: struct containing shell info
 * @crd: current directory
 *
 * Return: pointer to HOME or NULL if fail
 */
char *auxcd2(hshpack *sck, char *crd)
{
	char *h, *d = NULL;

	(void) crd;
	h = _getenv("HOME", *(sck->envCpy));
	if (h)
		d = h + 5;

	return (d);
}

/**
 * auxcd - auxiliary function of cd built in
 * @sck: struct containing shell info
 * @crd: the current directory
 *
 * Return: Pointer to dir or NULL if fail
 */
char *auxcd(hshpack *sck, char *crd)
{
	char *odp2 = NULL, *odp = NULL, *dr = NULL;

	if (sck->options[1] && sck->options[2])
	{
		write(2, "cd: too many arguments\n", 23);
		sck->exitnum[0] = 2;
		free(sck->options);
		free(crd);
		return (dr);
	}

	odp2 = _strdup(_getenv("OLDPWD", *(sck->envCpy)));
	if (odp2)
		odp = _strdup(odp2 + 7), free(odp2);
	if (!odp2)
	{
		odp = _strdup(crd);
	}

	dr = odp;

	return (dr);
}

/**
 * _cd_cmd - built in command cd
 * @sck: struct containing shell info
 *
 * Return: 1 if succesful, -1 if fail
 */
ssize_t _cd_cmd(hshpack *sck)
{
	char *c = NULL, *d = NULL, **nv, *oldpwd = NULL;
	int e = 1, check = 1, checkminus = 0;

	c = getcwd(NULL, 4096);
	if (!c)
		return (_error(4, sck, 2), free(sck->options), -1);
	if (!sck->options[1] ||
			(sck->options[1] && (!_strcmp(sck->options[1], "~"))))
	{
		d = auxcd2(sck, c);
		if (!d)
			return (free(sck->options), free(c), 1);
	}
	else
		if (!_strcmp(sck->options[1], "-"))
		{
			d = auxcd(sck, c);
			if (!d)
				return (free(sck->options), free(c), 1);
			checkminus = 1;
		}
		else
			d = sck->options[1];
	if (d)
		check = chdir(d);
	if (check == 0 && checkminus == 1)
		write(1, d, _strlen(d)), write(1, "\n", 1);
	if (check != 0)
		_error(4, sck, 2), e = -1;
	else
	{
		nv = _setenv(*(sck->envCpy), "PWD", d, sck);
		*(sck->envCpy) = nv;
		nv = _setenv(*(sck->envCpy), "OLDPWD", c, sck);
		*(sck->envCpy) = nv;
	}
	free(sck->options), free(c), free(oldpwd);
	if (checkminus == 1)
		free(d);
	return (e);
}
