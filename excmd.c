#include "header.h"
/**
  * execute_command - main function to execute cmd
  * @command: command to execute
  * @progname: name of program
  * Return: returns -1 on failure
  */
int execute_command(char *command, char *progname)
{
	//char *args[] = {"/bin/ls", "-l", NULL};
	char *args[4];
	char *token;
	int i = 0;

	token = strtok(command, " ");
	while (token != NULL && i < 4)
	{
		token[strcspn(token, "\n")] = '\0';
		args[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	args[i] = NULL;
	int status, exit_status;

	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		execve(args[0], args, NULL);
		perror(progname);
		exit(1);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			return (exit_status);
		}
		else
		{
			return (-1);
		}
	}
}
