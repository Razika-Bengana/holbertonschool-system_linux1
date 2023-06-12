#include "signals.h"

/**
 * main - entry point of the program
 * @argc: number of command-line argument
 * @argv: array of command-line argument strings
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */

int main(int argc, char *argv[])
{
	/*
	 * Convert the PID from string to integer using atoi
	 * and cast it to pid_t type
	 */
	pid_t pid = (pid_t)atoi(argv[1]);

	if (argc != 2)
	{
		printf("Usage: %s <pid>\n", argv[0]);
		return (EXIT_FAILURE);
	}

/* Send the SIGINT signal to the specified process using kill */
/* If the kill operation fails, return EXIT_FAILURE */
	if (kill(pid, SIGINT) != 0)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}
