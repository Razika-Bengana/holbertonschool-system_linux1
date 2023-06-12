#include "signals.h"

/**
 * sigint_handler - signal handler for SIGINT
 * @signum: signal number
 */

void sigint_handler(int signum)
{
	printf("Caught %d\n", signum);
	printf("Signal received\n");
	_Exit(EXIT_SUCCESS);
}

/**
 * main - entry point of the program
 * Return: 0 on success
 */

int main(void)
{
	struct sigaction sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGINT, &sa, NULL);

	pause(); /* Suspend indefinitely until a signal is received */

	return (0);
}
