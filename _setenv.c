#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
 * free_doubpoint - frees a double pointer array of strings
 * (must end in NULL)
 *
 * @pp: double pointer to free
 *
 * Return: no return
 */
void free_doubpoint(char **pp)
{
	int j, len = 0;

	while (pp[len] != 0)
		len++;

	for (j = 0; j < len; j++)
	{
		free(pp[j]);
	}
	free(pp);
}
/**
 * _copydoublep - copies an array of strings (double pointer)
 *
 * @p: double pointer to copy
 * @old_size: original size of P
 * @new_size: size of copy
 *
 * Return: Pointer malloec
 */
char **_copydoublep(char **pp, int osize, int nsize)
{
	char **cy;
	int ii, csize;

	if (!pp && (osize == nsize))
		return (NULL);

	if (nsize < osize)
	{
		csize = nsize;
		cy = malloc(sizeof(char *) * (csize + 1));
	}
	else
	{
		csize = osize;
		cy = malloc(sizeof(char *) * (nsize + 1));
	}
	if (cy == 0)
		return (0);

	if (pp)
		for (ii = 0; ii < csize; ii++)
		{
			cy[ii] = _strdup(pp[ii]);
			if (cy[ii] == 0)
			{
				ii--;
				for (; ii >= 0; ii--)
					free(cy[ii]);
				free(cy);
				return (0);
			}
		}
	cy[nsize] = '\0';

	return (cy);
}
/**
 * _strlendp - calculates length of double pointer (ending in NULL)
 * @ss: double pointer
 *
 * Return: Length of double pointer
 *
 */
int _strlendp(char **ss)
{
	int i = 0;

	if (!ss)
		return (0);

	while (ss[i] != NULL)
		i++;
	return (i);
}
/**
 * _setenv - overwrite an env variable or creates it
 *
 * @env: array of env variables
 * @var: env variable to set
 * @val: value to set
 * @sck: struct with shell info
 *
 * Return: 0 on success, -1 on error
 */
char **_setenv(char **env, char *var, char *val, hshpack *sck)
{
	int n, m, c, l = 0, len = 0;
	char *envjoin, *envjoin2, *copydup, **copy;

	if (_strlen(var) == 0 || var == 0)
		return (_error(3, sck, 1), NULL);
	envjoin2 = str_concat(var, "=");
	if (envjoin2 == 0)
		return (_error(3, sck, 1), NULL);
	envjoin = str_concat(envjoin2, val), free(envjoin2);
	if (envjoin == 0)
		return (_error(3, sck, 1), NULL);
	l = _strlen(var), len = _strlendp(env);
	for (n = 0; env && env[n] != 0; n++)
	{
		for (c = 0, m = 0; m < l && env[n][m] != 0; m++)
		{
			if (var[m] == '=')
				return (free(envjoin), _error(3, sck, 2), NULL);
			if (env[n][m] == var[m])
				c++;
		}
		if (c == l && env[n][c] == '=')
		{
			free(env[n]), copydup = _strdup(envjoin), free(envjoin);
			if (copydup == 0)
				return (_error(3, sck, 1), NULL);
			return (env[n] = copydup, env);
		}
	}
	copy = _copydoublep(env, len, len + 1);
	if (env)
		free_doubpoint(env);
	if (copy == 0)
		return (free(envjoin), _error(3, sck, 1), NULL);
	env = copy, copydup = _strdup(envjoin), free(envjoin);
	if (copydup == 0)
		return (_error(3, sck, 1), NULL);
	return (env[len] = copydup, env);
}
