#include "shell.h"

/**
 * str_len - returns string length
 * @stk: string length to be check
 * Return: returns string integer length
 */

int str_len(char *stk)
{
	int xk = 0;

	if (!stk)
		return (0);

	while (*stk++)
		xk++;
	return (xk);
}

/**
 * str_cmp - it performs strangs lexicogarphic comparison
 * @stk1: first strang
 * @stk2: second strang
 * Return: returns -ve if s1 < s2, returns +ve if s1 > s2, zero if s1 == s2
 */

int str_cmp(char *stk1, char *stk2)
{
	while (*stk1 && *stk2)
	{
		if (*stk1 != *stk2)
			return (*stk1 - *stk2);
		stk1++;
		stk2++;
	}
	if (*stk1 == *stk2)
		return (0);
	else
		return (*stk1 < *stk2 ? -1 : 1);
}

/**
 * starts_with - it checks if needle starts with haystack
 * @haystack: searched string
 * @needle: substring to find
 * Return: returns address of next haystack char or NULL
 */

char *starts_with(const char *hstack, const char *needle)
{
	while (*needle)
		if (*needle++ != *hstack++)
			return (NULL);
	return ((char *)hstack);
}

/**
 * str_cat - it concatenates two strings
 * @destn: buffer destination
 * @src: buffer source
 * Return: returns destination buffer pointer
 */

char *str_cat(char *bdestn, char *src)
{
	char *retn = bdestn;

	while (*bdestn)
		bdestn++;
	while (*src)
		*bdestn++ = *src++;
	*bdestn = *src;
	return (retn);
}
