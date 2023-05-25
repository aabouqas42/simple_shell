#include "main.h"

/**
 * execute_command - Execute the command.
 * @arguments: The command arguments.
 * @history: The history of commands.
 * @line: The input line.
 */
void execute_command(char **arguments, int history, char *line)
{
	pid_t child_pid;
	int status, i = 0;

	child_pid = fork();

	if (child_pid == 0)
	{
		if (execve(arguments[0], arguments, environ) == -1)
		{
			check_error(arguments[0], history);
			free(line);
			while (arguments[i])
			{
				free(arguments[i]);
				i++;
			}
			free(arguments);
			exit(state);
		}
	}
	else if (child_pid > 0)
	{
		wait(&status);
		if (WIFEXITED(status))
			state = WEXITSTATUS(status);
	} else
	{
		perror("Error child");
		state = EXIT_FAILURE;
	}
}

/**
 * check_builtin_command - Check if the command is a built-in function.
 * @word: The command to compare.
 * Return: 1 if it is a built-in command, 0 otherwise.
 */
int check_builtin_command(char *word)
{
	int i = 0;

	builtin builtins[] = {
		{"exit", our_exit},
		{"env", print_environment},
		{NULL, NULL}
	};

	if (check_void(word) == 0)
		return (1);

	while (builtins[i].command != NULL)
	{
		if (my_strcmp(word, builtins[i].command, _strlen(word) - 1) == 0)
		{
			builtins[i].function(word);
			return (1);
		}
		i++;
	} return (0);
}

/**
 * check_path - Check if the first argument is a file
 * inside the PATH directories.
 * @str: The string from getline.
 * Return: An array of strings (double pointer).
 */
char **check_path(char *str)
{
	int i;
	char *env_path = "PATH=", *concat, *path;
	char **buffer, **array;
	struct stat st;

	array = create_buffer(str, " \n");

	if (array[0][0] == '.' && array[0][1] == '/')
		return (array);

	path = clean_path(_getenv(env_path));

	if (path)
	{
		buffer = create_buffer(path, ":\n");
		for (i = 0; buffer[i]; i++)
		{
			concat = concatenate_strings(buffer[i], array[0]);

			if (stat(concat, &st) == 0)
			{
				for (i = 0; buffer[i]; i++)
					free(buffer[i]);
					free(buffer);
					free(path);
					free(array[0]);
					array[0] = concat;
					return (array);
			}
			free(concat);
		}
		for (i = 0; buffer[i]; i++)
			free(buffer[i]);
			free(buffer);
	}
	free(path);
	return (array);
}

/**
 * clean_path - Make a copy of the PATH and verify if it starts with ':'.
 * @path_env: The PATH environment variable.
 * Return: A string with the final copy of PATH.
 */
char *clean_path(char *path_env)
{
	int i, j = 0;
	char *clean_path;

	if (path_env == NULL)
		return (NULL);

	clean_path = malloc(sizeof(char) * _strlen(path_env) - 4);

	if (path_env[5] == ':')
		clean_path[j++] = '.';

	for (i = 5; path_env[i]; j++, i++)
	{
		clean_path[j] = path_env[i];
	}
	clean_path[j] = '\0';
	return (clean_path);
}

/**
 * create_buffer - Create a buffer (double pointer).
 * @str: The string.
 * @delim: The delimiters.
 * Return: A buffer.
 */
char **create_buffer(char *str, char *delim)
{
	char *token;
	char **buffer;
	int count, j = 0;

	count = count_delimiters(str, delim);
	buffer = malloc(sizeof(char *) * (count + 1));
	token = strtok(str, delim);

	while (token)
	{
		buffer[j] = _strdup(token);
		token = strtok(NULL, delim);
		j++;
	}
	buffer[j] = NULL;
	return (buffer);
}
