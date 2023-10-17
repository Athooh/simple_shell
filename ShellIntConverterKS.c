#include "shell.h"

/**
 * is_interactive - if shell is interactive mode, it returns true
 * @info: The structure containing potential arguments.
 * Return: returns 1 if interactive mode, return 0 otherwise
 */

int is_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->read_file_descriptor <= 2);
}

/**
 * is_delim - it checks if character is delimeter
 * @ch: the char checked
 * @dlmtr: delimeter string
 * Return: return 1 if true, 0 if false
 */

int is_delim(char ch, char *dlmtr)
{
	while (*dlmtr)
		if (*dlmtr++ == ch)
			return (1);
	return (0);
}

/**
 * _isalpha - it checks alphabetic character
 * @ch: input character
 * Return: returns 1 if ch is alphabetic, 0 otherwise
 */

int _isalpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * string_to_int - it converts string to an integer
 * @string: the converted string
 * Return: returns 0 if no numbers in string, converted number otherwise
 */

int string_to_int(char *string)
{
	int xk, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (xk = 0; string[xk] != '\0' && flag != 2; xk++)
	{
		if (string[xk] == '-')
			sign *= -1;

		if (string[xk] >= '0' && string[xk] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (string[xk] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
