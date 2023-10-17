#include "shell.h"

/**
 * is_chain - it test if current buffer char is a chain delimeter
 * @info: The structure containing potential arguments.
 * @buf: buffer char
 * @pstn: current position address in buf
 * Return: 1 if chain delimeter, 0 otherwise
 */

int is_chain(info_t *info, char *buf, size_t *pstn)
{
	size_t p = *pstn;

	if (buf[p] == '|' && buf[p + 1] == '|')
	{
		buf[p] = 0;
		p++;
		info->command_buffer_type = CMD_OR;
	}
	else if (buf[p] == '&' && buf[p + 1] == '&')
	{
		buf[p] = 0;
		p++;
		info->command_buffer_type = CMD_AND;
	}
	else if (buf[p] == ';')
	{
		buf[p] = 0;
		info->command_buffer_type = CMD_CHAIN;
	}
	else
		return (0);
	*pstn = p;
	return (1);
}

/**
 * check_chain - the checks to continue chaining based on last status
 * @info: The structure containing potential arguments.
 * @buf: character buffer
 * @pstn: current position address in buf
 * @idx: starting position in buf
 * @len: buf length
 * Return: returns Void
 */

void check_chain(info_t *info, char *buf, size_t *pstn, size_t idx, size_t len)
{
	size_t x = *pstn;

	if (info->command_buffer_type == CMD_AND)
	{
		if (info->command_status)
		{
			buf[idx] = 0;
			x = len;
		}
	}
	if (info->command_buffer_type == CMD_OR)
	{
		if (!info->command_status)
		{
			buf[idx] = 0;
			x = len;
		}
	}

	*pstn = x;
}

/**
 * alias_rep - it replaces aliases in the tokenized string
 * @info: The structure containing potential arguments.
 * Return: returns 1 if replaced, 0 otherwise
 */

int alias_rep(info_t *info)
{
	int x;
	list_t *node;
	char *s;

	for (x = 0; x < 10; x++)
	{
		node = node_startswith(info->alias_list, info->input_array[0], '=');
		if (!node)
			return (0);
		free(info->input_array[0]);
		s = str_chr(node->str, '=');
		if (!s)
			return (0);
		s = str_dup(s + 1);
		if (!s)
			return (0);
		info->input_array[0] = s;
	}
	return (1);
}

/**
 * vars_rep - it replaces vars in the tokenized string
 * @info: The structure containing potential arguments.
 * Return: returns 1 if replaced, 0 otherwise
 */

int vars_rep(info_t *info)
{
	int x = 0;
	list_t *node;

	for (x = 0; info->input_array[x]; x++)
	{
		if (info->input_array[x][0] != '$' || !info->input_array[x][1])
			continue;

		if (!str_cmp(info->input_array[x], "$?"))
		{
			str_rep(&(info->input_array[x]),
					str_dup(convert_num(info->command_status, 10, 0)));
			continue;
		}
		if (!str_cmp(info->input_array[x], "$$"))
		{
			str_rep(&(info->input_array[x]),
					str_dup(convert_num(getpid(), 10, 0)));
			continue;
		}
		node = node_startswith(info->env_variable, &info->input_array[x][1], '=');
		if (node)
		{
			str_rep(&(info->input_array[x]),
					str_dup(str_chr(node->str, '=') + 1));
			continue;
		}
		str_rep(&info->input_array[x], str_dup(""));

	}
	return (0);
}

/**
 * str_rep - it replaces string
 * @ol: old string address
 * @nw: new string
 * Return: returns 1 if replaced, 0 otherwise
 */

int str_rep(char **ol, char *nw)
{
	free(*ol);
	*ol = nw;
	return (1);
}
