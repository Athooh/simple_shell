#include "shell.h"

/**
 * *str_n_cpy - it copies a string
 * @dest: string destination to copy to
 * @src: string source
 * @mk: amount of copied characters
 * Return: returns the concatenated string
 */

char *str_n_cpy(char *dest, char *src, int mk)
{
	int xk, jk;
	char *stk = dest;

	xk = 0;
	while (src[xk] != '\0' && xk < mk - 1)
	{
		dest[xk] = src[xk];
		xk++;
	}
	if (xk < mk)
	{
		jk = xk;
		while (jk < mk)
		{
			dest[jk] = '\0';
			jk++;
		}
	}
	return (stk);
}

/**
 * *str_n_cat - it concatenates two strings
 * @dest: first string
 * @src: second string
 * @mk: the maximum amount of bytes to be used
 * Return: returns the concatenated string
 */

char *str_n_cat(char *dest, char *src, int mk)
{
	int xk, jk;
	char *stk = dest;

	xk = 0;
	jk = 0;
	while (dest[xk] != '\0')
		xk++;
	while (src[jk] != '\0' && jk < mk)
	{
		dest[xk] = src[jk];
		xk++;
		jk++;
	}
	if (jk < mk)
		dest[xk] = '\0';
	return (stk);
}

/**
 * *str_chr - it locates character in a string
 * @stk: the parsed string
 * @ch: the looked for character
 * Return: (st) a pointer to the memory area st
 */

char *str_chr(char *stk, char ch)
{
	do {
		if (*stk == ch)
			return (stk);
	} while (*stk++ != '\0');

	return (NULL);
}
