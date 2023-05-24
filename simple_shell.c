char command[MAX_COMMAND_LENGTH];
    char *args[MAX_COMMAND_LENGTH];
    char *token;
    pid_t pid;
    int i, status;

    while (1)
	{
		printf("#cisfun$ ");
		fgets(command, sizeof(command), stdin)
		
		if (feof(stdin))
		{
			printf("\n");
			break;
		}
		i = 0;
		token = strtok(command, " \n");
		while (token != NULL)
		{
			args[i++] = token;
			token = strtok(NULL, " \n");
			args[i] = NULL;
		}
		pid = fork();
		if (pid == -1)
		{
		perror("fork");
		exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			execvp(args[0], args);
			perror("execvp");
			exit(EXIT_FAILURE);
		} else
		{
			waitpid(pid, &status, 0);
		}		
    return 0;
	}
