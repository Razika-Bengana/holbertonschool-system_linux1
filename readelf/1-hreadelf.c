#include "header.h"

/**
 * main - displays the information contained in the ELF sections' headers
 * of an ELF file
 * @argc: argument count
 * @argv: the argument vector
 * @env:  the environment variable
 * Return: 0 (success), -1 (failure)
 */
int main(int argc, char **argv, char **env)
{
	char *args[] = {"/usr/bin/readelf", "-W", "-S", "", NULL};

	(void)argc;
	args[3] = argv[1];
	if (execve("/usr/bin/readelf", args, env) == -1)
	{
		perror("execv");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
