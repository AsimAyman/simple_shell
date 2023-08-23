#include <stdlib.h>
#include "shell.h"

/**
 * str_concat - concatenates two strings
 * @ss1: string1
 * @ss2: string2
 *
 * Return: Pointer
 */
char *str_concat(char *ss1, char *ss2)
{
	int ll1, ll2, n, m;
	char *ps;
	char *nnul = "";

	if (ss1 == NULL)
		ss1 = nnul;
	if (ss2 == NULL)
		ss2 = nnul;

	ll1 = 0, ll2 = 0;
	while (*(ss1 + ll1))
		ll1++;
	while (*(ss2 + ll2))
		ll2++;

	ps = malloc(sizeof(char) * (ll1 + ll2 + 1));

	if (ps == 0)
		return (0);

	for (n = 0; n < ll1; n++)
		*(ps + n) = *(ss1 + n);

	for (n = 0, m = ll1; n <= ll2; m++, n++)
		*(ps + m) = *(ss2 + n);

	return (ps);
}
