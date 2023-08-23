#include "shell.h"

/**
 * info_cpy - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 *
 * Return: new env or alias.
 */
char *info_cpy(char *name, char *value)
{
	int len_name, len_value, len;
	char *new;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");
	return (new);
}

/**
 * _sets_env - sets an env variable
 * @name: name of env
 * @value: value of env
 * @shell_data: Struct
 * Return: void
 */
void _sets_env(char *name, char *value, arg_list *shell_data)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; shell_data->_environ[i]; i++)
	{
		var_env = _strdup(shell_data->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(shell_data->_environ[i]);
			shell_data->_environ[i] = info_cpy(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	shell_data->_environ = _realloc_dup(shell_data->_environ,
	i, sizeof(char *) * (i + 2));
	shell_data->_environ[i] = info_cpy(name, value);
	shell_data->_environ[i + 1] = NULL;
}

/**
 * cmp_setenv - compares env var names
 * @shell_data: Struct
 * Return: 1 on success
 */
int cmp_setenv(arg_list *shell_data)
{

	if (shell_data->args[1] == NULL || shell_data->args[2] == NULL)
	{
		fetch_error(shell_data, -1);
		return (1);
	}
	_sets_env(shell_data->args[1], shell_data->args[2], shell_data);

	return (1);
}

/**
 * _unsetenv - deletes a env var
 * @shell_data: Struct
 * Return: 1 on success
 */
int _unsetenv(arg_list *shell_data)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (shell_data->args[1] == NULL)
	{
		fetch_error(shell_data, -1);
		return (1);
	}
	k = -1;
	for (i = 0; shell_data->_environ[i]; i++)
	{
		var_env = _strdup(shell_data->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, shell_data->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		fetch_error(shell_data, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; shell_data->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = shell_data->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(shell_data->_environ[k]);
	free(shell_data->_environ);
	shell_data->_environ = realloc_environ;
	return (1);
}
