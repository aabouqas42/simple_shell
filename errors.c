#include "shell.h"

/**
 * exit_err - gets error message for exit
 * @shell_data: Struct
 * Return: the error msg
 */
char *exit_err(arg_list *shell_data)
{
	char *ver_str;
	int length;
	char *error;

	ver_str = _itoa(shell_data->counter);
	length = _strlen(shell_data->av[0]) + _strlen(ver_str);
	length += _strlen(shell_data->args[0]) + _strlen(shell_data->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, shell_data->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, shell_data->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, shell_data->args[1]);
	_strcat(error, "\n\0");
	free(ver_str);

	return (error);
}

/**
 * fetch_cd_err - gets error message
 * @shell_data: Struct data
 * Return: the error message
 */
char *fetch_cd_err(arg_list *shell_data)
{
	char *error, *ver_str, *msg;
	int length, len_id;

	ver_str = _itoa(shell_data->counter);
	if (shell_data->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(shell_data->args[1]);
	}

	length = _strlen(shell_data->av[0]) + _strlen(shell_data->args[0]);
	length += _strlen(ver_str) + _strlen(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = cd_strcat_err(shell_data, msg, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * handle_cmd_unfound - generates error message for cmd not found
 * @shell_data: Struct
 * Return: the error message
 */
char *handle_cmd_unfound(arg_list *shell_data)
{
	char *ver_str;
	int length;
	char *error;

	ver_str = _itoa(shell_data->counter);
	length = _strlen(shell_data->av[0]) + _strlen(ver_str);
	length += _strlen(shell_data->args[0]) + 16;
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
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * cd_strcat_err - concatenates message for cd error
 * @shell_data: Struct
 * @msg: message
 * @error: error message
 * @ver_str: counter lines
 * Return: the error message
 */
char *cd_strcat_err(arg_list *shell_data, char *msg,
char *error, char *ver_str)
{
	char *illegal_flag;

	_strcpy(error, shell_data->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, shell_data->args[0]);
	_strcat(error, msg);
	if (shell_data->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = shell_data->args[1][1];
		illegal_flag[2] = '\0';
		_strcat(error, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_strcat(error, shell_data->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}
