#include "shell.h"

/**
 * get_environ - it returns the environ string array copy
 * @info: The structure containing potential arguments.
 * Return: returns 0 always
 */

char **get_environ(info_t *info)
{
	if (!info->modified_env_variable || info->environment_changed)
	{
		info->modified_env_variable = list_strings(info->env_variable);
		info->environment_changed = 0;
	}

	return (info->modified_env_variable);
}

/**
 * unset_env - it remove an env variable
 * @info: The structure containing potential arguments.
 * Return: returns 1 on delete, 0 otherwise
 * @var: string env var property
 */

int unset_env(info_t *info, char *var)
{
	list_t *node = info->env_variable;
	size_t x = 0;
	char *q;

	if (!node || !var)
		return (0);

	while (node)
	{
		q = starts_with(node->str, var);
		if (q && *q == '=')
		{
			info->environment_changed = delete_node_at_index(&(info->env_variable), x);
			x = 0;
			node = info->env_variable;
			continue;
		}
		node = node->next;
		x++;
	}
	return (info->environment_changed);
}

/**
 * set_env - it Initialize new env variable,
 *             or modify an existing one
 * @info: The structure containing potential arguments.
 * @var: string env var property
 * @value: string env var value
 * Return: returns 0 always
 */

int set_env(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *q;

	if (!var || !value)
		return (0);

	buf = malloc(str_len(var) + str_len(value) + 2);
	if (!buf)
		return (1);
	str_cpy(buf, var);
	str_cat(buf, "=");
	str_cat(buf, value);
	node = info->env_variable;
	while (node)
	{
		q = starts_with(node->str, var);
		if (q && *q == '=')
		{
			free(node->str);
			node->str = buf;
			info->environment_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env_variable), buf, 0);
	free(buf);
	info->environment_changed = 1;
	return (0);
}
