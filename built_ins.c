#include <limits.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "shell.h"

/**
 * _exit_cmd - built in command exit
 * @sck: struct containing shell info
 *
 * Return: -1 if error
 */
ssize_t _exit_cmd(hshpack *sck)
{
	long vToExit;

	if (sck->options[1] == NULL || _isnumber(sck->options[1]))
	{
		vToExit = _atoi(sck->options[1]);

		if (vToExit >= 0 && vToExit < INT_MAX)
		{
			if (vToExit > 255)
				vToExit %= 256;
			if (sck->options[1] == NULL)
				vToExit = sck->exitnum[0];
			free(*(sck->options));
			free(sck->options);
			if (*(sck->envCpy))
				free_doubpoint(*(sck->envCpy));
			free(sck);
			exit(vToExit);
		}
	}

	_error(2, sck, 2);
	free(sck->options);
	return (-1);
}
/**
 * _env_cmd - built in command env
 * @sck: struct containing shell info
 *
 * Return: 1 if succesful
 */
ssize_t _env_cmd(hshpack *sck)
{
	char **s;
	int c = 1;

	if (*(sck->envCpy) == NULL)
	{
		write(2, "Environment is Null, Can't Print it\n", 36);
		sck->exitnum[0] = 2;
		free(sck->options);
		return (-1);
	}

	s = *(sck->envCpy);

	if (sck->options[1] == NULL)
	{
		for (; s && *s; s++)
		{
			write(1, *s, _strlen(*s));
			write(1, "\n", 1);
		}
	}
	else
	{
		_error(0, sck, 2);
		c = -1;
	}

	free(sck->options);
	return (c);
}
/**
 * _setenv_cmd - built in command setenv
 * @sck: struct containing shell info
 *
 * Return: 1 if succesful, -1 if fail
 */
ssize_t _setenv_cmd(hshpack *sck)
{
	char **nv;
	char *var = NULL;
	char *val = NULL;

	if (sck->options[1])
	{
		var = sck->options[1];
		if (!sck->options[2])
		{
			write(2, "Invalid VALUE\n", 14);
			sck->exitnum[0] = 2;
			free(sck->options);
			return (-1);
		}
		else
			val = sck->options[2];

	}
	if (var == 0)
	{
		write(2, "Invalid VARIABLE\n", 17);
		sck->exitnum[0] = 2;
		free(sck->options);
		return (-1);
	}

	nv = _setenv(*(sck->envCpy), var, val, sck);

	if (nv == 0)
	{
		free(sck->options);
		return (-1);
	}

	*(sck->envCpy) = nv;
	free(sck->options);
	return (1);
}
/**
 * _unsetenv_cmd - built in command unsetenv
 * @sck: struct containing shell info
 *
 * Return: 1 if succesful, -1 if fail
 */
ssize_t _unsetenv_cmd(hshpack *sck)
{
	char **nv;
	char *var = NULL;

	if (sck->options[1])
		var = sck->options[1];
	else
	{
		sck->exitnum[0] = 2;
		write(2, "Please provide an argument\n", 27);
		return (free(sck->options), -1);
	}

	if (var == 0)
	{
		free(sck->options);
		return (1);
	}

	nv = _unsetenv(*(sck->envCpy), var, sck);

	if (nv == 0 && sck->unsetnull[0] == 0)
	{
		free(sck->options);
		sck->exitnum[0] = 2;
		return (-1);
	}

	*(sck->envCpy) = nv;
	free(sck->options);
	return (1);
}

/**
 * built_ints - checks if cmd is a built in
 * @sck: struct containing shell info
 *
 * Return: On fail 0
 */
ssize_t built_ints(hshpack *sck)
{
	b_ins ops[] = {
		{"exit", _exit_cmd},
		{"env", _env_cmd},
		{"setenv", _setenv_cmd},
		{"unsetenv", _unsetenv_cmd},
		{"cd", _cd_cmd},
		{"help", _help_cmd}
	};

	int i = 6, builtcheck; /* lenght of ops array */

	while (i--)
		if (!_strcmp(sck->cmd, ops[i].cmd))
		{
			sck->errnum[0] += 1;
			builtcheck = ops[i].f(sck);
			if (builtcheck == 1)
				sck->exitnum[0] = 0;
			return (builtcheck);
		}

	return (0);
}
