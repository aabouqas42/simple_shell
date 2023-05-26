#include "main.h"

/**
 * _fullpathbuffer - finds the string to call execve on
 * @av: pointer to array of user strings
 * @PATH: pointer to PATH string
 * @copy: pointer to copy of PATH string
 *
 * Return: a pointer to string to call execve on
 */
char *_fullpathbuffer(char **av, char *PATH, char *copy)
{
	char *tok, *full_path_buffer = NULL, *concat_str = NULL;
	static char tmp[256];
	int PATH_count = 0, full_path_flag = 0, z = 0, tok_len = 0;
	struct stat h;

	copy = NULL;
	copy = _strdup(PATH);
	PATH_count = _splitPATH(copy);
	tok = strtok(copy, ": =");
	while (tok != NULL)
	{
	concat_str = _concat(tmp, av, tok);
	if (stat(concat_str, &h) == 0)
	{
	full_path_buffer = concat_str;
	full_path_flag = 1;
	break;
	}
	if (z < PATH_count - 2)
	{
	tok_len = _strlen(tok);
	if (tok[tok_len + 1] == ':')
	{
	if (stat(av[0], &h) == 0)
	{
	full_path_buffer = av[0];
	full_path_flag = 1;
	break;
	}
	}
	}
	z++;
	tok = strtok(NULL, ":");
	}
	if (full_path_flag == 0)
	full_path_buffer = av[0];
	free(copy);
	return (full_path_buffer);
	}

/**
 * checkbuiltins - check if first user string is a built-in
 * @av: pointer to array of user strings
 * @buffer: pointer to user string
 * @exit_status: exit status of execve
 *
 * Return: 1 if user string is equal to env or 0 otherwise
 */
int checkbuiltins(char **av, char *buffer, int exit_status)
{
int i;

	if (_strcmp(av[0], "env") == 0)
	{
	_env();
	for (i = 0; av[i]; i++)
	free(av[i]);
	free(av);
	free(buffer);
	return (1);
	}
	else if (_strcmp(av[0], "exit") == 0)
	{
	for (i = 0; av[i]; i++)
	free(av[i]);
	free(av);
	free(buffer);
	exit(exit_status);
	}
	else
	return (0);
	}

/**
 * _forkprocess - create child process to execute based on user input
 * @av: pointer to array of user strings
 * @buffer: pointer to user string
 * @full_path_buffer: pointer to user input
 *
 * Return: 0 on success
 */
int _forkprocess(char **av, char *buffer, char *full_path_buffer)
{
int status;
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
	perror("Error");
	return (1);
	}
	if (child_pid == 0)
	{
	execve(full_path_buffer, av, NULL);
	perror("Error");
	for (status = 0; av[status]; status++)
	free(av[status]);
	free(av);
	free(buffer);
	exit(0);
	}
	else
	{
	wait(&status);
	if (WIFEXITED(status))
	return ((WEXITSTATUS(status)));
	}
	return (0);
	}
