#include "signals.h"

/**
 * current_handler_sigaction - Function that retrieves the current handler
 * of the SIGINT signal using sigaction
 *
 * This function retrieves the current handler of the SIGINT signal using the
 * sigaction function.
 * It returns a pointer to the current handler function for SIGINT.
 *
 * Return: Pointer to the current handler function for SIGINT,
 * or NULL on failure
 */

void (*current_handler_sigaction(void))(int)
{
	struct sigaction sa;

	if (sigaction(SIGINT, NULL, &sa) == -1)
	{
		return (NULL);  /* Failed to retrieve signal handler */
	}

	return (sa.sa_handler);  /* Return the current signal handler */
}
