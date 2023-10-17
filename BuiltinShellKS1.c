#include "shell.h"

/**
 * hist_list - it displays history list, a command per line, preceded
 *              with line numbers, starting at 0.
 * @info: The structure containing potential arguments.
 * Return: returns 0 Always
 */

int hist_list(info_t *info)
{
	printed_list(info->history_list);
	return (0);
}

/**
 * unset_alias - it sets alias to string
 * @info: The structure containing potential arguments.
 * @str: string alias
 * Return: returns 0 on success, 1 on error
 */

int unset_alias(info_t *info, char *str)
{
	char *q, c;
	int retn;

	q = str_chr(str, '=');
	if (!q)
		return (1);
	c = *q;
	*q = 0;
	retn = delete_node_at_index(&(info->alias_list),
		node_index(info->alias_list, node_startswith(info->alias_list, str, -1)));
	*q = c;
	return (retn);
}

/**
 * set_alias - it sets alias to string
 * @info: The structure containing potential arguments.
 * @str: string alias
 * Return: returns 0 on success, 1 on error
 */

int set_alias(info_t *info, char *str)
{
	char *q;

	q = str_chr(str, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias_list), str, 0) == NULL);
}

/**
 * print_alias - it prints an alias string
 * @node: alias node
 * Return: returns 0 on success, 1 on error
 */

int print_alias(list_t *node)
{
	char *q = NULL, *a = NULL;

	if (node)
	{
		q = str_chr(node->str, '=');
		for (a = node->str; a <= q; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(q + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - it mimics the alias builtin (man alias)
 * @info: The structure containing potential arguments.
 * Return: returns 0 Always
 */

int _myalias(info_t *info)
{
	int x = 0;
	char *q = NULL;
	list_t *node = NULL;

	if (info->argument_count == 1)
	{
		node = info->alias_list;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (x = 1; info->input_array[x]; x++)
	{
		q = str_chr(info->input_array[x], '=');
		if (q)
			set_alias(info, info->input_array[x]);
		else
			print_alias(node_startswith(info->alias_list, info->input_array[x], '='));
	}

	return (0);
}
