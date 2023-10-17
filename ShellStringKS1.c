#include "shell.h"

/**
 * str_cpy - it copies a string
 * @bdestn: buffer destination
 * @src: source
 * Return: returns destination pointer
 */

char *str_cpy(char *bdestn, char *src)
{
	int x = 0;

	if (bdestn == src || src == 0)
		return (bdestn);
	while (src[x])
	{
		bdestn[x] = src[x];
		x++;
	}
	bdestn[x] = 0;
	return (bdestn);
}

/**
 * str_dup - stirng duplicator
 * @str: string duplicated
 * Return: returns duplicated string pointer
 */

char *str_dup(const char *str)
{
	int length = 0;
	char *retn;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	retn = malloc(sizeof(char) * (length + 1));
	if (!retn)
		return (NULL);
	for (length++; length--;)
		retn[length] = *--str;
	return (retn);
}

/**
 * _puts - it prints string input
 * @str: string printed
 * Return: returns nothing
 */

void _puts(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_putchar(str[x]);
		x++;
	}
}

/**
 * _putchar -it writes character c to stdout
 * @ch: character printed
 * Return: returns 1 On success.
 * On error, -1 is returned, & errno set appropriately.
 */

int _putchar(char ch)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(1, buf, x);
		x = 0;
	}
	if (ch != BUF_FLUSH)
		buf[x++] = ch;
	return (1);
}
