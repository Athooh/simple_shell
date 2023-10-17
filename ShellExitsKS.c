#include "shell.h"

/**
 * *str_n_cpy - it copies a string
 * @dest: string destination to copy to
 * @src: string source
 * @m: amount of copied characters
 * Return: returns the concatenated string
 */

char *str_n_cpy(char *dest, char *src, int m)
{
	int x, j;
	char *st = dest;

	x = 0;
	while (src[x] != '\0' && x < m - 1)
	{
		dest[x] = src[x];
		x++;
	}
	if (x < m)
	{
		j = x;
		while (j < m)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (st);
}

/**
 * *str_n_cat - it concatenates two strings
 * @dest: first string
 * @src: second string
 * @m: the maximum amount of bytes to be used
 * Return: returns the concatenated string
 */

char *str_n_cat(char *dest, char *src, int m)
{
	int x, j;
	char *st = dest;

	x = 0;
	j = 0;
	while (dest[x] != '\0')
		x++;
	while (src[j] != '\0' && j < m)
	{
		dest[x] = src[j];
		x++;
		j++;
	}
	if (j < m)
		dest[x] = '\0';
	return (st);
}

/**
 * *str_chr - it locates character in a string
 * @st: the parsed string
 * @ch: the looked for character
 * Return: (st) a pointer to the memory area st
 */

char *str_chr(char *st, char ch)
{
	do {
		if (*st == ch)
			return (st);
	} while (*st++ != '\0');

	return (NULL);
}
