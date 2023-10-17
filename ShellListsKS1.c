#include "shell.h"

/**
 * printed_list -it prints all the elements of list_t linked list
 * @h: first node pointer
 * Return: returns size of list
 */

size_t printed_list(const list_t *h)
{
	size_t s = 0;

	while (h)
	{
		_puts(convert_num(h->numb, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		s++;
	}
	return (s);
}

/**
 * list_length - it determines linked list length
 * @x: first node pointer
 * Return: returns size of list
 */

size_t list_length(const list_t *x)
{
	size_t n = 0;

	while (x)
	{
		x = x->next;
		n++;
	}
	return (n);
}

/**
 * node_index - gets the node index
 * @hd: list head pointer
 * @node: the node pointer
 * Return: returns index of node or -1 if unsuccessful
 */

ssize_t node_index(list_t *hd, list_t *node)
{
	size_t x = 0;

	while (hd)
	{
		if (hd == node)
			return (x);
		hd = hd->next;
		x++;
	}
	return (-1);
}

/**
 * list_strings - it returns string array of the list->str
 * @hd: first node pointer
 * Return: returns the array of strings
 */

char **list_strings(list_t *hd)
{
	list_t *node = hd;
	size_t x = list_length(hd), j;
	char **strs;
	char *str;

	if (!hd || !x)
		return (NULL);
	strs = malloc(sizeof(char *) * (x + 1));
	if (!strs)
		return (NULL);
	for (x = 0; node; node = node->next, x++)
	{
		str = malloc(str_len(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < x; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = str_cpy(str, node->str);
		strs[x] = str;
	}
	strs[x] = NULL;
	return (strs);
}

/**
 * node_startswith - it returns node with string starting with prefix
 * @node: list head pointer
 * @prefix: the string to match
 * @chr: next character after prefix to match
 * Return: returns match node or null
 */

list_t *node_startswith(list_t *node, char *prefix, char chr)
{
	char *q = NULL;

	while (node)
	{
		q = starts_with(node->str, prefix);
		if (q && ((chr == -1) || (*q == chr)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
