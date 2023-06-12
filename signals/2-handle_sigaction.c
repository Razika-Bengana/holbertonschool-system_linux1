#include "signals.h"

/**
 * sigint_handler - Handler function for the SIGINT signal
 *
 * This function is called when the SIGINT signal (Ctrl+C) is received.
 * It prints "Gotcha! [signum]" to indicate the signal that was caught.
 *
 * @signum: The signal number
 *
 * Return: nothing (void)
 */

void sigint_handler(int signum)
{
	printf("Gotcha! [%d]\n", signum);
	fflush(stdout);
}

/**
 * handle_sigaction - Sets a handler for the SIGINT signal using sigaction
 *
 * This function sets the handler for the SIGINT signal using
 * the sigaction function.
 * It associates the sigint_handler function with the SIGINT signal.
 *
 * Return: 0 on success, -1 on error (failed to set the signal handler)
 */

int handle_sigaction(void)
{
	struct sigaction sa;

	sa.sa_handler = sigint_handler;  /* Set the handler function */
	sa.sa_flags = 0;

	/* Initialize the signal mask to an empty set */
	sigemptyset(&sa.sa_mask);

	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		return (-1);  /* Failed to set the signal handler */
	}

	return (0);  /* Signal handler successfully set */
}
