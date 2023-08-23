#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include "shell.h"

/**
 * _strtok - tokenizes a string based on a delimiter
 *
 * @s: string to operate
 * @d: delimiter
 *
 * Return: pointer to string
 * or NULL if there is no match
 *
 */
char *_strtok(char *s, const char *d)
{
	const char *o = d;
	int isEqual = 1, isGetInto = 0;
	static char *stp, *stpnull;
	static int isEnd;

	if (s)
		isEnd = 0;
	if (isEnd)
		return (NULL);
	stp = (s) ? s : (stpnull + 1);
	if (s)
		stpnull = s;
	else
		s = stp;
	while (*s && isEqual)
	{
		isEqual = 0;
		for (d = o; *d; d++)
			if (*s == *d)
				isEqual = 1;
		s = (!isEqual) ? s : s + 1;
		isEnd = (*s) ? 0 : 1;
		if (isEnd)
			return (NULL);
	}
	stp = s;
	while (*s && !isEqual)
	{
		isEqual = 0;
		for (d = o; *d; d++)
			if (*s == *d)
			{
				isGetInto = 1, isEqual = 1;
				isEnd = (*(s + 1)) ? 0 : 1, *s = '\0';
			}
		s = (isEqual) ? s : s + 1;
		if (!isGetInto && !*s)
			isEnd = 1;
	}
	return (stpnull = s, stp);
}
