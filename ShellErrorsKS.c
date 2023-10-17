#include "shell.h"

/**
 * _erratoi - it converts string to an integer
 * @st: the converted string
 * Return: returns 0 if no numbers in string, converted number otherwise
 *       returns -1 on error
 */

int _erratoi(char *st)
{
	int x = 0;
	unsigned long int result = 0;

	if (*st == '+')
		st++;
	for (x = 0;  st[x] != '\0'; x++)
	{
		if (st[x] >= '0' && st[x] <= '9')
		{
			result *= 10;
			result += (st[x] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - it prints error message
 * @info: The structure containing potential arguments.
 * @err_str: the string containing specified error type
 * Return: returns 0 if no numbers in string, converted number otherwise
 *        returns -1 on error
 */

void print_error(info_t *info, char *err_str)
{
	eput_str(info->program_filename);
	eput_str(": ");
	print_d(info->error_count, STDERR_FILENO);
	eput_str(": ");
	eput_str(info->input_array[0]);
	eput_str(": ");
	eput_str(err_str);
}

/**
 * print_d - function to print decimal (integer) number (base 10)
 * @input: the input
 * @fdr: the filedescriptor to write on
 * Return: returns number of printed characters
 */

int print_d(int input, int fdr)
{
	int (*__putchar)(char) = _putchar;
	int x, count = 0;
	unsigned int _abs_, current;

	if (fdr == STDERR_FILENO)
		__putchar = eput_char;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (x = 1000000000; x > 1; x /= 10)
	{
		if (_abs_ / x)
		{
			__putchar('0' + current / x);
			count++;
		}
		current %= x;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_num - function converter, str-word clone
 * @numb: the number
 * @base: the base
 * @flags: flags argument
 * Return: returns string
 */

char *convert_num(long int numb, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = numb;

	if (!(flags & CONVERT_UNSIGNED) && numb < 0)
	{
		n = -numb;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - it replaces first instance of '#' with '\0'
 * @buf: string modified address
 * Return: returns 0 always;
 */

void remove_comments(char *buf)
{
	int x;

	for (x = 0; buf[x] != '\0'; x++)
		if (buf[x] == '#' && (!x || buf[x - 1] == ' '))
		{
			buf[x] = '\0';
			break;
		}
}
