#include "shell.h"

/**
 * input_buf - it buffers chained commands
 * @info: The structure containing potential arguments.
 * @buf: buffer address
 * @len: len var address
 * Return: returns bytes read
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->count_current_line = 1;
			remove_comments(*buf);
			build_hist_list(info, *buf, info->hist_line_count++);
			{
				*len = r;
				info->command_buffer = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - it gets a line minus the newline
 * @info: The structure containing potential arguments.
 * Return: returns bytes read
 */

ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t x, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->input_string), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = x;
		p = buf + x;

		check_chain(info, buf, &j, x, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		x = j + 1;
		if (x >= len)
		{
			x = len = 0;
			info->command_buffer_type = CMD_NORM;
		}

		*buf_p = p;
		return (str_len(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - it reads a buffer
 * @info: The structure containing potential arguments.
 * @buf: the buffer
 * @x: the size
 * Return: it returns rs
 */

ssize_t read_buf(info_t *info, char *buf, size_t *x)
{
	ssize_t r = 0;

	if (*x)
		return (0);
	r = read(info->read_file_descriptor, buf, READ_BUF_SIZE);
	if (r >= 0)
		*x = r;
	return (r);
}

/**
 * _getline - it gets next line of input from STDIN
 * @info: The structure containing potential arguments.
 * @ptr: buffer address pointed to, preallocated or NULL
 * @length: the size of preallocated ptr buffer if not NULL
 * Return: returns ss
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t x;
	ssize_t r = 0, s = 0;
	char *q = NULL, *new_p = NULL, *c;

	q = *ptr;
	if (q && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = str_chr(buf + i, '\n');
	x = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = mem_realloc(q, s, s ? s + x : x + 1);
	if (!new_p)
		return (q ? free(q), -1 : -1);

	if (s)
		str_n_cat(new_p, buf + i, x - i);
	else
		str_n_cpy(new_p, buf + i, x - i + 1);

	s += x - i;
	i = x;
	q = new_p;

	if (length)
		*length = s;
	*ptr = q;
	return (s);
}

/**
 * sigintHandler - it blocks ctrl-C
 * @sig_numb: signal number
 * Return: returns void
 */

void sigintHandler(__attribute__((unused))int sig_numb)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
