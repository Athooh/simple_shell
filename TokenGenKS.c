#include "shell.h"

/**
 * **string_to_words2 - it splits string into words
 * @str: string input
 * @dlmtr: delimeter
 * Return: returns array of strings pointer, NULL on failure
 */

char **string_to_words2(char *str, char dlmtr)
{
	int x, j, k, m, numwords = 0;
	char **st;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (x = 0; str[x] != '\0'; x++)
		if ((str[x] != dlmtr && str[x + 1] == dlmtr) ||
				    (str[x] != dlmtr && !str[x + 1]) || str[x + 1] == dlmtr)
			numwords++;
	if (numwords == 0)
		return (NULL);
	st = malloc((1 + numwords) * sizeof(char *));
	if (!st)
		return (NULL);
	for (x = 0, j = 0; j < numwords; j++)
	{
		while (str[x] == dlmtr && str[x] != dlmtr)
			x++;
		k = 0;
		while (str[x + k] != dlmtr && str[x + k] && str[x + k] != dlmtr)
			k++;
		st[j] = malloc((k + 1) * sizeof(char));
		if (!st[j])
		{
			for (k = 0; k < j; k++)
				free(st[k]);
			free(st);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			st[j][m] = str[x++];
		st[j][m] = 0;
	}
	st[j] = NULL;
	return (st);
}

/**
 * **string_to_words - it splits string into words. Repeat delimiters ignored
 * @str: the string input
 * @dlmtr: string delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **string_to_words(char *str, char *dlmtr)
{
	int x, j, k, m, numwords = 0;
	char **st;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!dlmtr)
		dlmtr = " ";
	for (x = 0; str[x] != '\0'; x++)
		if (!is_delim(str[x], dlmtr) && (is_delim(str[x + 1], dlmtr) || !str[x + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	st = malloc((1 + numwords) * sizeof(char *));
	if (!st)
		return (NULL);
	for (x = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[x], dlmtr))
			x++;
		k = 0;
		while (!is_delim(str[x + k], dlmtr) && str[x + k])
			k++;
		st[j] = malloc((k + 1) * sizeof(char));
		if (!st[j])
		{
			for (k = 0; k < j; k++)
				free(st[k]);
			free(st);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			st[j][m] = str[x++];
		st[j][m] = 0;
	}
	st[j] = NULL;
	return (st);
}
