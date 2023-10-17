#include "shell.h"

/**
 * eput_str - it prints input string
 * @str: printed string
 * Return: returns nothing
 */

void eput_str(char *str)
{
	int xs = 0;

	if (!str)
		return;
	while (str[xs] != '\0')
	{
		eput_char(str[xs]);
		xs++;
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
	static int xs;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || xs >= WRITE_BUF_SIZE)
	{
		write(2, buf, xs);
		xs = 0;
	}
	if (ch != BUF_FLUSH)
		buf[xs++] = ch;
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
	static int xs;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || xs >= WRITE_BUF_SIZE)
	{
		write(fdr, buf, xs);
		xs = 0;
	}
	if (ch != BUF_FLUSH)
		buf[xs++] = ch;
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
	int xs = 0;

	if (!str)
		return (0);
	while (*str)
	{
		xs += _putfd(*str++, fdr);
	}
	return (xs);
}
