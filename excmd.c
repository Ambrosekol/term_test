#include "header.h"
/**
  * execute_command - main function to execute cmd
  * @command: command to execute
  * @progname: name of program
  * Return: returns -1 on failure
  */
int execute_command(char *command, char *progname)
{
	char *args[2];
	int status, exit_status;

	args[0] = command;
	args[1] = NULL;
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		execve(command, args, NULL);
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
