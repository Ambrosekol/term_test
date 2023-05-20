#include "header.h"
#include <errno.h>
int execfun(char **args, char *progname)
{
	char path[20] = PATH;
	char *comnd = args[0];
	int status;

	if ((int) strcspn(args[0], "/") == 0)
	{
		status = execve(args[0], args, NULL);

		if (status == -1)
		{
			if (errno == ENOENT)
			{
				freopen("/dev/null", "w", stderr);
				printf("%s: 1: %s: not found\n", progname, comnd);
			}
			else
			{
				perror("execve");
			}
		}
	}
	else
	{
		strcat(path, "/");
		strcat(path, args[0]);
		status = execve(path, args, NULL);

		if (status == -1) 
		{
			if (errno == ENOENT)
			{
				freopen("/dev/null", "w", stderr);
				printf("%s: 1: %s: not found\n", progname, comnd);
			}
			else
			{
				perror("execve");
			}
		}
	}
	return (status);
}
