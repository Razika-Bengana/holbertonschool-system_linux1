#include "signals.h"

/**
 * pid_exist - function that checks if a process exists given its PID.
 *
 * @pid: The process ID to check.
 *
 * Return: 1 if the process exists, 0 otherwise.
 */

int pid_exist(pid_t pid)
{

/*
 *Sending a null signal (0) to the process to check its existence
 * without affecting it.
 * If the kill function returns 0, the process exists.
 */
	if (kill(pid, 0) == 0)
	{
		return (1);
	}
	else
	{
/*
 * If the kill function returns -1, the process doesn't exist
 * or we don't have permission to send the signal.
 */
		return (0);
	}
}
