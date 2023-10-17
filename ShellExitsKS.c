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
	char *st = dest;

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
	return (st);
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
	char *st = dest;

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
	return (st);
}

/**
 * *str_chr - it locates character in a string
 * @st: the parsed string
 * @chk: the looked for character
 * Return: (st) a pointer to the memory area st
 */

char *str_chr(char *st, char chk)
{
	do {
		if (*st == chk)
			return (st);
	} while (*st++ != '\0');

	return (NULL);
}
