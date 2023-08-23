#include "shell.h"

/**
 * cd_home - moves to home dir
 * @shell_data: Struct
 * Return: void
 */
void cd_home(arg_list *shell_data)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", shell_data->_environ);

	if (home == NULL)
	{
		_sets_env("OLDPWD", p_pwd, shell_data);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		fetch_error(shell_data, 2);
		free(p_pwd);
		return;
	}

	_sets_env("OLDPWD", p_pwd, shell_data);
	_sets_env("PWD", home, shell_data);
	free(p_pwd);
	shell_data->status = 0;
}

/**
 * sh_cd - function to change current directory
 * @shell_data: Struct
 * Return: 1 on success.
 */
int sh_cd(arg_list *shell_data)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = shell_data->args[1];

	if (dir != NULL)
	{
		ishome = _strcmp("$HOME", dir);
		ishome2 = _strcmp("~", dir);
		isddash = _strcmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_home(shell_data);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_back(shell_data);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_parentdir(shell_data);
		return (1);
	}

	cd_pathdir(shell_data);

	return (1);
}

/**
 * cd_pathdir - moves to specified dir
 * @shell_data: Struct
 * Return: void
 */
void cd_pathdir(arg_list *shell_data)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = shell_data->args[1];
	if (chdir(dir) == -1)
	{
		fetch_error(shell_data, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	_sets_env("OLDPWD", cp_pwd, shell_data);

	cp_dir = _strdup(dir);
	_sets_env("PWD", cp_dir, shell_data);

	free(cp_pwd);
	free(cp_dir);

	shell_data->status = 0;

	chdir(dir);
}

/**
 * cd_parentdir - moves to parent directory
 * @shell_data: Struct
 * Return: Void
 */
void cd_parentdir(arg_list *shell_data)
{
	char *dir, *cp_pwd, *cp_strtok_pwd;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	_sets_env("OLDPWD", cp_pwd, shell_data);
	dir = shell_data->args[1];
	if (_strcmp(".", dir) == 0)
	{
		_sets_env("PWD", cp_pwd, shell_data);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	reverse_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			reverse_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		_sets_env("PWD", cp_strtok_pwd, shell_data);
	}
	else
	{
		chdir("/");
		_sets_env("PWD", "/", shell_data);
	}
	shell_data->status = 0;
	free(cp_pwd);
}

/**
 * cd_back - moves to previous dir
 * @shell_data: Struct
 * Return: void
 */
void cd_back(arg_list *shell_data)
{
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", shell_data->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	_sets_env("OLDPWD", cp_pwd, shell_data);

	if (chdir(cp_oldpwd) == -1)
		_sets_env("PWD", cp_pwd, shell_data);
	else
		_sets_env("PWD", cp_oldpwd, shell_data);

	p_pwd = _getenv("PWD", shell_data->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	shell_data->status = 0;

	chdir(p_pwd);
}
