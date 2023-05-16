#include "header.h"
/**
  * execute_command - main function to execute cmd
  * @command: command to execute
  * @progname: name of program
  * Return: returns -1 on failure
  */
int execute_command(char __attribute__((unused)) *command, char *progname)
{
	//char *args[] = {"/bin/", "ls", "-l", NULL};
	char *args[8];
	char *token;
	int exstatus;
	int i = 0;
	int status; //exit_status;

	token = strtok(command, " ");
	while (token != NULL && i < 8)
	{
		token[strcspn(token, "\n")] = '\0';
		args[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	args[i] = NULL;
	if (args[0] == NULL)
		return (0);
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		exstatus = execfun(args);
		//execve(args[0], args, NULL);
		perror(progname);
		exit(exstatus);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
		//	exit_status = WEXITSTATUS(status);
		//	return (exit_status);
		}
		else
		{
			return (-1);
		}
	}
}
