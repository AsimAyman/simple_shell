#include <stdlib.h>
#include "shell.h"

/**
 * _strcpy - copy a source input ont destinated input
 * @d: target where will be stored the input
 * @s: source to copy from
 *
 *
 * Return: dest address
 * On error: -1 inapropiate entry
 */

char *_strcpy(char *d, char *s)
{
	int j = 0;

	for (j = 0; *(s + j) != '\0'; j++)
		*(d + j) = *(s + j);

	*(d + j) = *(s + j);

	return (d);
}

/**
 * _strlen - function that returns the length of a string
 * @s: string address
 *
 *
 * Return: nothing
 * On error: -1 inapropiate entry
 */

int _strlen(char *s)
{
	return ((!*s) ? 0 : 1 + _strlen(s + 1));
}

/**
 * _strdup - function that returns a pointer to a newly allocated space
 * in memory, which contains a copy of the string given as a parameter
 * @s: source to copy
 *
 *
 * Return: address where is stored the result
 * On error: -1 inapropiate entry
 */

char *_strdup(char *s)
{
	char *ar;

	if (!s)
		return (NULL);

	ar = malloc((_strlen(s) * sizeof(*ar)) + 1);

	if (!ar)
		return (NULL);

	_strcpy(ar, s);

	return (ar);
}
