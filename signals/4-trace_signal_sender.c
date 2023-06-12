#include "signals.h"

/**
 * sigquit_handler - Signal handler for SIGQUIT
 *
 * This function is registered as the handler for SIGQUIT signal.
 * It prints the PID of the process that sent the SIGQUIT signal.
 *
 * @signum: Signal code
 * @si: Pointer to siginfo_t structure containing additional signal information
 * @ucontext: Pointer to ucontext_t structure containing the execution context
 *
 * Return: nothing (void)
 */

void sigquit_handler(int signum, siginfo_t *si, void *ucontext)
{
	(void)ucontext; /* Unused parameter */

	if (signum == SIGQUIT)
		printf("SIGQUIT sent by %u\n", si->si_pid);
}

/**
 * trace_signal_sender - Sets up signal handler for SIGQUIT
 *
 * This function sets up the signal handler for SIGQUIT using sigaction.
 * It registers the sigquit_handler function as the handler for SIGQUIT.
 *
 * Return: 0 on success, -1 on failure
 */

int trace_signal_sender(void)
{
	struct sigaction sa;

	sa.sa_sigaction = sigquit_handler; /* Use the sigquit_handler function */
	return (sigaction(SIGQUIT, &sa, NULL));
}
