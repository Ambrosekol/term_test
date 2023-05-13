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
/*	char *fileinit = NULL; */
	/** ssize_t input_file; **/

	if (argc > 1)
	{
		printf("Usage: %s [file]\n", argv[0]);
		return (1);
	}
	if (isatty(STDIN_FILENO))
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
			/** entry point of code **/
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
	else
	{
		if (getline(&command, &wrn, stdin) != 0)
		{
			command[strcspn(command, "\n")] = '\0';
			/** entry point of code **/
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
	return (0);
}
