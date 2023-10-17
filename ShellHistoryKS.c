#include "shell.h"

/**
 * get_hist_file - it gets history file
 * @info: The structure containing potential arguments.
 * Return: returns allocated string containg history file
 */

char *get_hist_file(info_t *info)
{
	char *buf, *dir;

	dir = get_env(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (str_len(dir) + str_len(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	str_cpy(buf, dir);
	str_cat(buf, "/");
	str_cat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - it creates a file, or appends to existing file
 * @info: The structure containing potential arguments.
 * Return: returns 1 on success, else -1
 */

int write_history(info_t *info)
{
	ssize_t fdr;
	char *filename = get_hist_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fdr = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fdr == -1)
		return (-1);
	for (node = info->history_list; node; node = node->next)
	{
		_putsfd(node->str, fdr);
		_putfd('\n', fdr);
	}
	_putfd(BUF_FLUSH, fdr);
	close(fdr);
	return (1);
}

/**
 * read_history - it reads history from file
 * @info: The structure containing potential arguments.
 * Return: returns histcount on success, 0 otherwise
 */

int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fdr, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_hist_file(info);

	if (!filename)
		return (0);

	fdr = open(filename, O_RDONLY);
	free(filename);
	if (fdr == -1)
		return (0);
	if (!fstat(fdr, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fdr, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fdr);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_hist_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_hist_list(info, buf + last, linecount++);
	free(buf);
	info->hist_line_count = linecount;
	while (info->hist_line_count-- >= HIST_MAX)
		delete_node_at_index(&(info->history_list), 0);
	renumber_history(info);
	return (info->hist_line_count);
}

/**
 * build_hist_list - it adds entry to history linked list
 * @info: The structure containing potential arguments.
 * @buf: the buffer
 * @linecount: the history linecount, histcount
 * Return: returns 0 Always
 */

int build_hist_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history_list)
		node = info->history_list;
	add_node_end(&node, buf, linecount);

	if (!info->history_list)
		info->history_list = node;
	return (0);
}

/**
 * renumber_history - it renumbers the history linked list after changes
 * @info: The structure containing potential arguments.
 * Return: the new histcount
 */

int renumber_history(info_t *info)
{
	list_t *node = info->history_list;
	int x = 0;

	while (node)
	{
		node->numb = x++;
		node = node->next;
	}
	return (info->hist_line_count = x);
}
