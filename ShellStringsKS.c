#include "shell.h"

/**
 * str_len - returns string length
 * @st: string length to be check
 * Return: returns string integer length
 */

int str_len(char *st)
{
	int x = 0;

	if (!st)
		return (0);

	while (*st++)
		x++;
	return (x);
}

/**
 * str_cmp - it performs strangs lexicogarphic comparison
 * @st1: first strang
 * @st2: second strang
 * Return: returns -ve if st1 < st2, returns +ve if st1 > st2, zero if st1 == st2
 */

int str_cmp(char *st1, char *st2)
{
	while (*st1 && *st2)
	{
		if (*st1 != *st2)
			return (*st1 - *st2);
		st1++;
		st2++;
	}
	if (*st1 == *st2)
		return (0);
	else
		return (*st1 < *st2 ? -1 : 1);
}

/**
 * starts_with - it checks if needle starts with haystack
 * @hstack: searched string
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

char *str_cat(char *destn, char *src)
{
	char *retn = destn;

	while (*destn)
		destn++;
	while (*src)
		*destn++ = *src++;
	*destn = *src;
	return (retn);
}
