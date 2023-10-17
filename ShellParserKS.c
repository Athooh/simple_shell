#include "shell.h"

/**
 * path_finder - it finds this cmd in PATH string
 * @info: The structure containing potential arguments.
 * @strpath: string PATH
 * @cmd: cmd to be found
 * Return: returns full path of cmd if found or returns NULL
 */

char *path_finder(info_t *info, char *strpath, char *cmd)
{
	int x = 0, curr_psn = 0;
	char *current_path;

	if (!strpath)
		return (NULL);
	if ((str_len(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_exe_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!strpath[x] || strpath[x] == ':')
		{
			current_path = dups_chars(strpath, curr_psn, x);
			if (!*current_path)
				str_cat(current_path, cmd);
			else
			{
				str_cat(current_path, "/");
				str_cat(current_path, cmd);
			}
			if (is_exe_cmd(info, current_path))
				return (current_path);
			if (!strpath[x])
				break;
			curr_psn = x;
		}
		x++;
	}
	return (NULL);
}

/**
 * is_exe_cmd - determines whether a file is an executable command
 * @info: The structure containing potential arguments.
 * @path: file path
 * Return: returns 1 if true, return 0 otherwise
 */

int is_exe_cmd(info_t *info, char *path)
{
	struct stat stt;

	(void)info;
	if (!path || stat(path, &stt))
		return (0);

	if (stt.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dups_chars - it duplicates the characters
 * @strpath: the string PATH
 * @strt: the starting index
 * @stp: the stopping index
 * Return: returns new buffer pointer
 */

char *dups_chars(char *strpath, int strt, int stp)
{
	static char buf[1024];
	int x = 0, s = 0;

	for (s = 0, x = strt; x < stp; x++)
		if (strpath[x] != ':')
			buf[s++] = strpath[x];
	buf[s] = 0;
	return (buf);
}
