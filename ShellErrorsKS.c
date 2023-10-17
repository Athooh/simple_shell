#include "shell.h"

/**
 * eput_str - it prints input string
 * @str: printed string
 * Return: returns nothing
 */

void eput_str(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		eput_char(str[x]);
		x++;
	}
}

/**
 * eput_char - it writes character c to stderr
 * @ch: character to print
 * Return: returns 1 On success.
 * returns -1 on error, and errno is set appropriately.
 */

int eput_char(char ch)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(2, buf, x);
		x = 0;
	}
	if (ch != BUF_FLUSH)
		buf[x++] = ch;
	return (1);
}

/**
 * _putfd - it writes character c to given fdr
 * @ch: printed character
 * @fdr: filedescriptor to write on
 * Return: returns 1 on success.
 * returns -1 on error, and errno is set appropriately.
 */

int _putfd(char ch, int fdr)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(fdr, buf, x);
		x = 0;
	}
	if (ch != BUF_FLUSH)
		buf[x++] = ch;
	return (1);
}

/**
 * _putsfd - it prints string input
 * @str: the printed string
 * @fdr: filedescriptor to write on
 * Return: returns the number of chars put
 */

int _putsfd(char *str, int fdr)
{
	int x = 0;

	if (!str)
		return (0);
	while (*str)
	{
		x += _putfd(*str++, fdr);
	}
	return (x);
}
