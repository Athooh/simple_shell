#include "shell.h"

/**
 * shl_exit - Exit the shell
 * @info: the structure containing potential arguments.
 * Return: It exits the shell with the specified exit status
 * (0) if command is "exit"; otherwise, it continues the program.
 */

int shl_exit(info_t *info)
{
	int exitcheck;

	if (info->input_array[1])
	{
		exitcheck = _erratoi(info->input_array[1]);
		if (exitcheck == -1)
		{
			info->command_status = 2;
			print_error(info, "Illegal number: ");
			eput_str(info->input_array[1]);
			eput_char('\n');
			return (1);
		}
		info->err_code = _erratoi(info->input_array[1]);
		return (-2);
	}
	info->err_code = -1;
	return (-2);
}

/**
 * _cwd - it changes the process current directory
 * @info: the structure containing potential arguments.
 * Return: returns 0 Always
 */

int _cwd(info_t *info)
{
	char *sts, *dir, buffer[1024];
	int chdir_retn;

	sts = getcwd(buffer, 1024);
	if (!sts)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->input_array[1])
	{
		dir = get_env(info, "HOME=");
		if (!dir)
			chdir_retn = chdir((dir = get_env(info, "PWD=")) ? dir : "/");
		else
			chdir_retn = chdir(dir);
	}
	else if (str_cmp(info->input_array[1], "-") == 0)
	{
		if (!get_env(info, "OLDPWD="))
		{
			_puts(sts);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(info, "OLDPWD=")), _putchar('\n');
		chdir_retn = chdir((dir = get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_retn = chdir(info->input_array[1]);
	if (chdir_retn == -1)
	{
		print_error(info, "can't cd to ");
		eput_str(info->input_array[1]), eput_char('\n');
	}
	else
	{
		set_env(info, "OLDPWD", get_env(info, "PWD="));
		set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _cpd - it changes the current process directory
 * @info: the structure containing potential arguments.
 * Return: returns 0 Always
 */

int _cpd(info_t *info)
{
	char **arg_array;

	arg_array = info->input_array;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
