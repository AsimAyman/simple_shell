#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
 * _copydoublepDel - copies an array of strings (double pointer)
 *
 * @p: double pointer to copy
 * @nsize: size of copy
 * @jmp: value that must be skipped in copy
 *
 * Return: Pointer malloec
 */
char **_copydoublepDel(char **p, int nsize, int jmp)
{
	char **c;
	int n, m, csize;

	csize = nsize;
	c = malloc(sizeof(char *) * (csize + 1));
	if (c == 0)
		return (0);

	for (n = 0, m = 0; m < csize; n++, m++)
	{
		if (n == jmp)
			n++;
		c[m] = _strdup(p[n]);
		if (c[m] == 0)
		{
			m--;
			for (; m >= 0; m--)
				free(c[m]);
			free(c);
			return (0);
		}
	}

	c[nsize] = '\0';

	return (c);
}

/**
 * _unsetenv - unsets an enviromental variable
 *
 * @ev: array of env variables
 * @var: env variable to unset
 * @sck: struct with shell info
 *
 * Return: 0 on success, -1 on error
 */
char **_unsetenv(char **ev, char *var, hshpack *sck)
{
	int n, m, c, l = 0, l = 0, f = 0;
	char **cpy;

	sck->unsetnull[0] = 0;
	if (!ev)
		return (write(2, "Environment is NULL\n", 20), NULL);
	if (_strlen(var) == 0 || var == 0)
		return (_error(3, sck, 1), NULL);
	l = _strlen(var), l = _strlendp(ev);
	for (n = 0; ev[n] != 0; n++)
	{
		for (c = 0, m = 0; m < l && ev[n][m] != 0; m++)
		{
			if (var[m] == '=')
				return (_error(3, sck, 2), NULL);
			if (ev[n][m] == var[m])
				c++;
		}
		if (c == l && ev[n][c] == '=')
		{
			f = 1;
			if ((l - 1) != 0)
			{
				cpy = _copydoublepDel(ev, l - 1, n);
				if (cpy == 0)
					return (_error(7, sck, 1), NULL);
			}
			else
				sck->unsetnull[0] = 1, cpy = NULL;
			free_doubpoint(ev), ev = cpy;
			return (ev);
		}
	}
	if (f == 0)
		return (write(2, "VARIABLE not found\n", 19), NULL);
	return (ev);
}
