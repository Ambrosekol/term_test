#include "header.h"
/**
  * main - start of program
  * @argc: argument count
  * @argv: argument vector
  * Return: returns int
  */
int main(int argc, char *argv[])
{
	char *command = NULL;
	size_t wrn = 0;
	int status;
	ssize_t input_file;

	if (argc == 1)
	{
		while (1)
		{
			printf("$ ");
			if (getline(&command, &wrn, stdin) == 0)
			{
				printf("\n");
				break;
			}
			command[strcspn(command, "\n")] = '\0';
			if (strcmp(command, "exit") == 0)
			{
				break;
			}
			/**entry point of code**/
			status = execute_command(command, argv[0]);
			/**==================================**/
			if (status == -1)
			{
				printf("%s:, No such file or directory.\n", argv[0]);
			}
			free(command);
			command = NULL;
		}
	}
	else if (argc == 2)
	{
		input_file = open(argv[1], O_RDONLY);
		if (input_file < 0)
		{
			perror(argv[1]);
			return (1);
		}
		while (read(input_file, command, MAX_COMMAND_LENGTH) != 0)
		{
			/** Remove newline character **/
			command[strcspn(command, "\n")] = '\0';
			/** Temporarily redirect stderr to a pipe **/
			int stderr_pipe[2];
			pipe(stderr_pipe);
			int original_stderr = dup(STDERR_FILENO);
			dup2(stderr_pipe[1], STDERR_FILENO);
			close(stderr_pipe[1]);
			status = execute_command(command, argv[0]);
			/** Read from the pipe to capture stderr output **/
			char stderr_output[90];
			memset(stderr_output, 0, sizeof(stderr_output));
			read(stderr_pipe[0], stderr_output, sizeof(stderr_output));
			close(stderr_pipe[0]);
			/** Restore stderr **/
			dup2(original_stderr, STDERR_FILENO);
			if (status == -1)
			{
				printf("%s\n", stderr_output);
			}
		}
		close(input_file);
	}
	else
	{
		printf("Usage: %s [file]\n", argv[0]);
		return (1);
	}
	return (0);
}
