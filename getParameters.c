#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include "shell.h"
/**
 * getParameters - obtains parameters from buffer of prompt
 * @rBuffer: raw_buffer
 * @sck: struct containing shell info
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
char **getParameters(char *rBuffer, hshpack *sck)
{
	char **b, *cp_buffer;
	ssize_t cnt = 0, j = 0;

	cp_buffer = _strdup(rBuffer);
	if (!cp_buffer)
	{
		_error(7, sck, 1);
		exit(-1);
	}

	if (_strtok(cp_buffer, " \n"))
		cnt++;
	else
	{
		free(cp_buffer);
		return (NULL);
	}
	while (_strtok(NULL, " \n"))
		cnt++;

	free(cp_buffer);
	b = malloc(sizeof(char *) * (cnt + 1));
	if (!b)
	{
		_error(7, sck, 1);
		exit(-1);
	}
	b[0] = _strtok(rBuffer, " \n");
	for (j = 1; j < cnt && b[j - 1]; j++)
		b[j] = _strtok(NULL, " \n");

	if (!b[j - 1])
	{
		free_doubpoint(b);
		return (NULL);
	}

	b[j] = NULL;
	return (b);
}
