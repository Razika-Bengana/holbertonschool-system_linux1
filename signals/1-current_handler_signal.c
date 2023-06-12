#include "signals.h"

/**
 * current_handler_signal - retrieves the current handler of the signal SIGINT
 *
 * This function retrieves the current handler function for the SIGINT signal.
 * It temporarily sets the handler to SIG_IGN (ignore) and then restores it
 * back to the original handler to ensure the handler is unchanged after calling
 * this function.
 *
 * Return: Pointer to the current handler function for SIGINT, or NULL on failure.
 */

void (*current_handler_signal(void))(int)
{
	sighandler_t handler;

	/* Set the handler to SIG_IGN (ignore) temporarily to get the current handler */
	handler = signal(SIGINT, SIG_IGN);

	if (handler == SIG_ERR)
	{
		return NULL; /* Failed to set the signal handler */
	}

	/* Restore the original handler and return the current handler */
	if (signal(SIGINT, handler) == SIG_ERR)
	{
		return NULL; /* Failed to set the signal handler back to the original handler */
	}

	return handler;
}
