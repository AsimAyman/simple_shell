#include <limits.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "shell.h"

/**
 * _pow - gets the result of base to ower
 * @b: base decimal
 * @p: power
 *
 * Return: result
 */
long _pow(long b, long p)
{
	long j = 0;
	long r = 1;

	for (j = 0; j < p; j++)
		r *= b;

	return (r);
}

/**
 * _atoi - convert a char input to int
 * @sc: char input
 *
 *
 * Return: input transformed to integer
 * On error: -1 inapropiate entry
 */

long _atoi(char *sc)
{
	long j = 0;
	long c = 0;
	long l = 0;
	unsigned long r = 0;
	long toR = 0;
	long m = 0;
	long ofset = 48;

	if (!sc)
		return (0);

	for (j = 0; *(sc + j) != '\0'; j++)
	{
		if (*(sc + j) >= 48 && *(sc + j) <= 57)
			l++;
		else if (l != 0)
			break;

		if (*(sc + j) == '-')
			m++;
	}

	for (j--; l > 0; j--, c++, l--)
		r +=  (*(sc + j) - ofset) * _pow(10, c);

	toR = (m % 2 != 0) ? r * (-1) : r;

	return (toR);
}
/**
 * _strcmp - compares two strings
 * @st1: string 1
 * @st2: string 2
 *
 * Return: 0 if strings are equal or another value if not
 *
 */
int _strcmp(char *st1, char *st2)
{
	int j = 0;
	int e = 0;

	for (j = 0; (*(st1 + j) || *(st2 + j)) && !e; j++)
		if (*(st1 + j) != *(st2 + j))
			e = *(st1 + j) - *(st2 + j);

	return (e);
}
/**
 * _isdigit - checks if a character is a digit
 * @cc: character
 *
 * Return: 1 if digit, 0 if not
 *
 */
int _isdigit(int cc)
{
	return ((cc >= 48 && cc <= 57) ? 1 : 0);
}
/**
 * _isnumber - checks if a string is composed of numbers
 * @st: string
 *
 * Return: 1 if string has only numbers, 0 if not
 */
int _isnumber(char *st)
{
	for (; *st; st++)
		if (!_isdigit(*st))
			return (0);
	return (1);
}
