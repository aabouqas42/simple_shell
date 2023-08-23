#include "shell.h"

/**
 * find_builtin - finds builtin cmd
 * @shell_data: Struct
 * Return: 1 on success
 */
int find_builtin(arg_list *shell_data)
{
	int (*builtin)(arg_list *shell_data);

	if (shell_data->args[0] == NULL)
		return (1);

	builtin = _fetch_builtin(shell_data->args[0]);

	if (builtin != NULL)
		return (builtin(shell_data));

	return (execute_cmd(shell_data));
}

/**
 * _fetch_builtin - gets builtin commands
 * @cmd: the command
 * Return: pointer to the command
 */
int (*_fetch_builtin(char *cmd))(arg_list *)
{
	built_ins builtin[] = {
		{ "env", print_env },
		{ "exit", sh_exit },
		{ "setenv", cmp_setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", sh_cd },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, cmd) == 0)
			break;
	}

	return (builtin[i].f);
}
