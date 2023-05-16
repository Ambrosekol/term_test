#include "header.h"

int execfun(char **args)
{
	char path[20] = PATH;
	int status;

	if ((int) strcspn(args[0], "/") == 0)
	{
		status = execve(args[0], args, NULL);
	}
	else
	{
		strcat(path, "/");
		strcat(path, args[0]);
		status = execve(path, args, NULL);
	}
	return (status);
}
