#include "shell.h"

/**
 * printed_list -it prints all the elements of list_t linked list
 * @fh: first node pointer
 * Return: returns size of list
 */

size_t printed_list(const list_t *fh)
{
	size_t sk = 0;

	while (fh)
	{
		_puts(convert_num(fh->numb, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(fh->str ? fh->str : "(nil)");
		_puts("\n");
		fh = fh->next;
		sk++;
	}
	return (sk);
}

/**
 * list_length - it determines linked list length
 * @xk: first node pointer
 * Return: returns size of list
 */

size_t list_length(const list_t *xk)
{
	size_t nk = 0;

	while (xk)
	{
		xk = xk->next;
		nk++;
	}
	return (nk);
}

/**
 * node_index - gets the node index
 * @lhd: list head pointer
 * @node: the node pointer
 * Return: returns index of node or -1 if unsuccessful
 */

ssize_t node_index(list_t *lhd, list_t *node)
{
	size_t xk = 0;

	while (lhd)
	{
		if (lhd == node)
			return (xk);
		lhd = lhd->next;
		xk++;
	}
	return (-1);
}

/**
 * list_strings - it returns string array of the list->str
 * @fhd: first node pointer
 * Return: returns the array of strings
 */

char **list_strings(list_t *fhd)
{
	list_t *node = fhd;
	size_t xk = list_length(fhd), jk;
	char **strs;
	char *str;

	if (!fhd || !xk)
		return (NULL);
	strs = malloc(sizeof(char *) * (xk + 1));
	if (!strs)
		return (NULL);
	for (xk = 0; node; node = node->next, xk++)
	{
		str = malloc(str_len(node->str) + 1);
		if (!str)
		{
			for (jk = 0; jk < xk; jk++)
				free(strs[jk]);
			free(strs);
			return (NULL);
		}

		str = str_cpy(str, node->str);
		strs[xk] = str;
	}
	strs[xk] = NULL;
	return (strs);
}

/**
 * printed_list -it prints all the elements of list_t linked list
 * @fh: first node pointer
 * Return: returns size of list
 */

size_t printed_list(const list_t *fh)
{
	size_t sk = 0;

	while (fh)
	{
		_puts(convert_num(fh->numb, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(fh->str ? fh->str : "(nil)");
		_puts("\n");
		fh = fh->next;
		sk++;
	}
	return (sk);
}

/**
 * node_startswith - it returns node with string starting with prefix
 * @node: list head pointer
 * @prefix: the string to match
 * @chrk: next character after prefix to match
 * Return: returns match node or null
 */

list_t *node_startswith(list_t *node, char *prefix, char chrk)
{
	char *qk = NULL;

	while (node)
	{
		qk = starts_with(node->str, prefix);
		if (qk && ((chrk == -1) || (*qk == chrk)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
