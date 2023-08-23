#include "shell.h"

/**
 * fetch_error - gets error messages
 * @shell_data: Struct
 * @eval: the value of the error
 * Return: eval
 */
int fetch_error(arg_list *shell_data, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = handle_getenv_err(shell_data);
		break;
	case 126:
		error = handle_path_err(shell_data);
		break;
	case 127:
		error = handle_cmd_unfound(shell_data);
		break;
	case 2:
		if (_strcmp("exit", shell_data->args[0]) == 0)
			error = exit_err(shell_data);
		else if (_strcmp("cd", shell_data->args[0]) == 0)
			error = fetch_cd_err(shell_data);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	shell_data->status = eval;
	return (eval);
}

/**
 * handle_path_err - generates error for path fail
 * @shell_data: Struct
 * Return: error message
 */
char *handle_path_err(arg_list *shell_data)
{
	char *ver_str;
	int length;
	char *error;

	ver_str = _itoa(shell_data->counter);
	length = _strlen(shell_data->av[0]) + _strlen(ver_str);
	length += _strlen(shell_data->args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, shell_data->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, shell_data->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * handle_getenv_err - getenv error
 * @shell_data: Struct
 * Return: the error message
 */
char *handle_getenv_err(arg_list *shell_data)
{
	char *ver_str;
	char *msg;
	int length;
	char *error;

	ver_str = _itoa(shell_data->counter);
	msg = ": Unable to add/remove from environment\n";
	length = _strlen(shell_data->av[0]) + _strlen(ver_str);
	length += _strlen(shell_data->args[0]) + _strlen(msg) + 4;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}

	_strcpy(error, shell_data->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, shell_data->args[0]);
	_strcat(error, msg);
	_strcat(error, "\0");
	free(ver_str);

	return (error);
}
