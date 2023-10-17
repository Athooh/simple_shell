#include "shell.h"

/**
 * my_env - it prints current environment
 * @info: The structure containing potential arguments.
 * Return: returns 0 Always
 */

int my_env(info_t *info)
{
	print_list_str(info->env_variable);
	return (0);
}

/**
 * get_env - it gets value of an env variable
 * @info: The structure containing potential arguments.
 * @name: the env var name
 * Return: returns the value
 */

char *get_env(info_t *info, const char *name)
{
	list_t *node = info->env_variable;
	char *qs;

	while (node)
	{
		qs = starts_with(node->strs, name);
		if (qs && *qs)
			return (qs);
		node = node->next;
	}
	return (NULL);
}

/**
 * my_set_env - it Initializes new env variable,
 * or modify an existing one
 * @info: The structure containing potential arguments.
 * Return: returns 0 Always
 */

int my_set_env(info_t *info)
{
	if (info->argument_count != 3)
	{
		eput_strs("Incorrect number of arguements\n");
		return (1);
	}
	if (set_env(info, info->input_array[1], info->input_array[2]))
		return (0);
	return (1);
}

/**
 * my_unset_env - it removes an env variable
 * @info: The structure containing potential arguments.
 * Return: returns 0 Always
 */

int my_unset_env(info_t *info)
{
	int xs;

	if (info->argument_count == 1)
	{
		eput_strs("Too few arguements.\n");
		return (1);
	}
	for (xs = 1; xs <= info->argument_count; xs++)
		unset_env(info, info->input_array[xs]);

	return (0);
}

/**
 * pop_env_list - it populates env linked list
 * @info: The structure containing potential arguments.
 * Return: returns 0 always
 */

int pop_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t xs;

	for (xs = 0; environ[xs]; xs++)
		add_node_end(&node, environ[xs], 0);
	info->env_variable = node;
	return (0);
}
