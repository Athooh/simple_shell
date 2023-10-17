#include "shell.h"

/**
 * shell_loop - shell main loop
 * @info: The structure containing potential arguments.
 * @va: vector arguments from main()
 * Return: returns 0 on success, and 1 on error(error code)
 */

int shell_loop(info_t *info, char **va)
{
	ssize_t s = 0;
	int builtin_retn = 0;

	while (s != -1 && builtin_retn != -2)
	{
		clear_info(info);
		if (is_interactive(info))
			_puts("$ ");
		eput_char(BUF_FLUSH);
		s = get_input(info);
		if (s != -1)
		{
			set_info(info, va);
			builtin_retn = find_builtin(info);
			if (builtin_retn == -1)
				cmd_find(info);
		}
		else if (is_interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!is_interactive(info) && info->command_status)
		exit(info->command_status);
	if (builtin_retn == -2)
	{
		if (info->err_code == -1)
			exit(info->command_status);
		exit(info->err_code);
	}
	return (builtin_retn);
}
/**
 * cmd_fork - it forks an exec thread to run command
 * @info: The structure containing potential arguments.
 * Return: returns void
 */

void cmd_fork(info_t *info)
{
	pid_t child_pd;

	child_pd = fork();
	if (child_pd == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pd == 0)
	{
		if (execve(info->current_path, info->input_array, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->command_status));
		if (WIFEXITED(info->command_status))
		{
			info->command_status = WEXITSTATUS(info->command_status);
			if (info->command_status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

/**
 * find_builtin - builtin command finder
 * @info: The structure containing potential arguments.
 * Return: returns -1 if builtin not found,
 * returns 0 if builtin executed successfully,
 * returns 1 if builtin found but not successful,
 * returns 2 if builtin signals exit()
 */

int find_builtin(info_t *info)
{
	int x, built_in_retn = -1;
	builtin_table builtintbl[] = {
		{"exit", shl_exit},
		{"env", my_env},
		{"help", _cpd},
		{"history", hist_list},
		{"setenv", my_set_env},
		{"unsetenv", my_unset_env},
		{"cd", _cwd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (x = 0; builtintbl[x].type; x++)
		if (str_cmp(info->input_array[0], builtintbl[x].type) == 0)
		{
			info->error_count++;
			built_in_retn = builtintbl[x].func(info);
			break;
		}
	return (built_in_retn);
}

/**
 * cmd_find - it finds command in PATH
 * @info: The structure containing potential arguments.
 * Return: returns void
 */

void cmd_find(info_t *info)
{
	char *current_path = NULL;
	int s, t;

	info->current_path = info->input_array[0];
	if (info->count_current_line == 1)
	{
		info->error_count++;
		info->count_current_line = 0;
	}
	for (s = 0, t = 0; info->input_string[s]; s++)
		if (!is_delim(info->input_string[s], " \t\n"))
			t++;
	if (!t)
		return;

	current_path = path_finder(info, get_env(info, "PATH="),
		info->input_array[0]);
	if (current_path)
	{
		info->current_path = current_path;
		cmd_fork(info);
	}
	else
	{
		if ((is_interactive(info) || get_env(info, "PATH=")
					|| info->input_array[0][0] == '/')
			&& is_exe_cmd(info, info->input_array[0]))
			cmd_fork(info);
		else if (*(info->input_string) != '\n')
		{
			info->command_status = 127;
			print_error(info, "not found\n");
		}
	}
}
