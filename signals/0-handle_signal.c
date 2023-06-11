#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

/**
 * sigint_handler - Handler function for the SIGINT signal.
 * It prints "Gotcha! [<signum>]" where <signum> is the signal number.
 *
 * @signum: the signal number
 *
 * Return: nothing (void)
 */

void sigint_handler(int signum)
{
	int count = 0;

	printf("Gotcha! [%d]\n", signum);

	/* If SIGINT is received 3 times, exit the program */
	if (count >= 3)
	{
		exit(0);
	}
}

/**
 * handle_signal - function that sets a handler for the SIGINT signal.
 *
 * This function registers a signal handler for the SIGINT signal (Ctrl+C).
 * When a SIGINT signal is received, the provided handler function
 * (sigint_handler) will be called.
 *
 * Return: 0 on success, or -1 if failed to set the signal handler
 */

int handle_signal(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		return (-1); /* Failed to set the signal handler */
	}

	return (0); /* Signal handler successfully set */
}
