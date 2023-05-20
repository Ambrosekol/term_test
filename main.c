#include "header.h"
/**
  * main - start of program
  * @argc: argument count
  * @argv: argument vector
  * Return: returns int
  */
int main(int argc, char *argv[])
{
	char *command = malloc(1024);
	size_t wrn = 0;
	ssize_t wrdcnt;
/*	char *fileinit = NULL; */
	/** ssize_t input_file; **/

	if (command == NULL)
	{
		printf("error in malloc");
	}
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
			wrdcnt = getline(&command, &wrn, stdin);
			if (wrdcnt <= 0)
			{
				printf("\n");
				break;
			}
			if (wrdcnt != EOF)
			{
				command[strcspn(command, "\n")] = '\0';
				if (strcmp(command, "exit") == 0)
				{
					break;
				}
				/** entry point of code **/
				//status = 
					execute_command(command, argv[0]);
				/**==================================**/
				/**if (status == -1)
				{
					printf("%s:, bNo such file or directory.\n", argv[0]);
				}**/
			}
		}
	}
	else
	{
		if (getline(&command, &wrn, stdin) != 0)
		{
			command[strcspn(command, "\n")] = '\0';
			/** entry point of code **/
			//status = 
			execute_command(command, argv[0]);
			/**==================================**/
			free(command);
			command = NULL;
			exit(127);
		}
	}
	free(command);
	return (0);
}
