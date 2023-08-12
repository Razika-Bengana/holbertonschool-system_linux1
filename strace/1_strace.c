#include "strace.h"
#include "syscalls.h"

int startSubprocess(char *args[], char *env[]);
int waitForSyscall(pid_t child);
int traceChild(pid_t child);


/**
 * startSubprocess - Create a subprocess to be traced
 *
 * @args: Array of command-line arguments
 * @env: Array of environmental variables
 *
 * Return: the value of execve or -1 if failed
 */

int startSubprocess(char *args[], char *env[])
{
	ptrace(PTRACE_TRACEME);
	kill(getpid(), SIGSTOP);
	return (execve(args[0], args, env));
}


/**
 * waitForSyscall - Wait for a syscall invocation in the subprocess
 *
 * @child: PID of the subprocess
 *
 * Return: 0 if syscall is called, 1 if subprocess is terminated
 */

int waitForSyscall(pid_t child)
{
	int status;

	while (1)
	{
		ptrace(PTRACE_SYSCALL, child, 0, 0);
		waitpid(child, &status, 0);
		if (WIFSTOPPED(status) && WSTOPSIG(status) & 0x80)
			return (0);
		if (WIFEXITED(status))
			break;
	}
	return (1);
}

/**
 * traceChild - Trace the system calls of a child process
 *
 * @child: PID of the child process
 *
 * Return: EXIT_SUCCESS on success, appropriate exit code on failure
 */

int traceChild(pid_t child)
{
	int status;
	long syscallNumber;

	waitpid(child, &status, 0);
	setbuf(stdout, NULL);
	ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_TRACESYSGOOD);

	while (1)
	{
		if (waitForSyscall(child) != 0)
			break;

		syscallNumber = ptrace(PTRACE_PEEKUSER, child, sizeof(long) * ORIG_RAX);
		fprintf(stdout, "%s", syscalls_64_g[syscallNumber].name);

		if (waitForSyscall(child) != 0)
			break;

		fprintf(stdout, "\n");
	}
	fprintf(stdout, "\n");
	return (EXIT_SUCCESS);
}

/**
 * main - Entry point
 *
 * @argc: Argument count
 * @argv: Argument vector
 * @envp: Environmental variables
 *
 * Return: EXIT_FAILURE if failed, EXIT_SUCCESS if successful
 */

int main(int argc, char *argv[], char *envp[])
{
	pid_t childPid;

	if (argc < 2)
	{
		fprintf(stderr, "%s command [args...]\n", argv[0]);
		return (EXIT_FAILURE);
	}

	childPid = fork();

	if (childPid < 0)
	{
		return (EXIT_FAILURE);
	}
	else if (childPid == 0)
	{
		return (startSubprocess(argv + 1, envp));
	}
	else
	{
		return (traceChild(childPid));
	}
}
