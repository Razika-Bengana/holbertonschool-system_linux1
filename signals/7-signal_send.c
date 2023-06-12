#include "signals.h"

/**
 * main - entry point of the program
 * @argc: number of command-line argument
 * @argv: array of command-line argument strings
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */

int main(int argc, char *argv[])
{
/* Check if the number of arguments is correct */
	if (argc != 2)
	{
		printf("Usage: %s <pid>\n", argv[0]);
		return (EXIT_FAILURE);
	}

/* Send SIGINT signal to the specified PID */
	if (kill((pid_t)atoi(argv[1]), SIGINT) != 0)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}
