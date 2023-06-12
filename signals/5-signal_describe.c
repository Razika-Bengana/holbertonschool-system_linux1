#include "signals.h"

/**
 * main - entry point, prints strsignal description for a given signum
 *
 * @argc: number of command line args
 * @argv: array of command line arg strings
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */

int main(int argc, char *argv[])
{
	/* Check if the number of command line arguments is correct */
	if (argc != 2)
	{
		/* Print the correct usage of the program */
		printf("Usage: %s <signum>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	/* Print the signal description for the given signal number */
	printf("%s: %s\n", argv[1], strsignal(atoi(argv[1])));

	return (EXIT_SUCCESS);
}
