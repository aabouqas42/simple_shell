#include "shell.h"

/**
 * check_exec_perm - checks for users permissions
 * @dir: dest directory
 * @shell_data: Struct
 * Return: 1 on fail
 */
int check_exec_perm(char *dir, arg_list *shell_data)
{
	if (dir == NULL)
	{
		fetch_error(shell_data, 127);
		return (1);
	}

	if (_strcmp(shell_data->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			fetch_error(shell_data, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(shell_data->args[0], X_OK) == -1)
		{
			fetch_error(shell_data, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * locate_cmd - finds command
 * @cmd: the command
 * @_environ: env variable
 * Return: command directory
 */
char *locate_cmd(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlen(cmd);
		token_path = _strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (if_current_dir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * if_current_dir - checks : in the current dir
 * @path: pointer char.
 * @i: index pointer
 * Return: 1 on success
 */
int if_current_dir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * if_exec - checks is a command is executable
 * @shell_data: struct
 * Return: 0 on fail
 */
int if_exec(arg_list *shell_data)
{
	char *input;
	int i;
	struct stat st;

	input = shell_data->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	fetch_error(shell_data, 127);
	return (-1);
}

/**
 * execute_cmd - executes command
 * @shell_data: struct
 * Return: 1 on success
 */
int execute_cmd(arg_list *shell_data)
{
	int exec;
	char *dir;
	pid_t pd;
	pid_t wpd;
	int state;
	(void) wpd;

	exec = if_exec(shell_data);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = locate_cmd(shell_data->args[0], shell_data->_environ);
		if (check_exec_perm(dir, shell_data) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = locate_cmd(shell_data->args[0], shell_data->_environ);
		else
			dir = shell_data->args[0];
		execve(dir + exec, shell_data->args, shell_data->_environ);
	}
	else if (pd < 0)
	{
		perror(shell_data->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	shell_data->status = state / 256;
	return (1);
}
