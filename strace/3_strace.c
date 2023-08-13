#include "strace.h"

/**
 * waitSyscall - program that waits for a syscall invocation in the subprocess
 *
 * @child: PID of the subprocess to trace
 *
 * Return: 0 if syscall is called, 1 if subprocess is terminated
 */

int waitSyscall(pid_t child)
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
 * printReg - program that prints a single register's value as part
 * of syscall arguments
 *
 * @regs: user registers struct containing register values
 * @idx: index of the parameter in syscall arguments
 * @reg: value of the register to print
 * @delim: delimiter to use when printing multiple arguments
 *
 * Return: nothing (void)
 */

void printReg(struct user_regs_struct regs, int idx, ulong reg, char *delim)
{
	if (syscalls_64_g[regs.orig_rax].params[idx] != (type_t)-1 &&
	    syscalls_64_g[regs.orig_rax].params[idx] != VOID)
	{
		if (syscalls_64_g[regs.orig_rax].params[idx] == VARARGS)
			fprintf(stdout, "%s...", delim);
		else
			fprintf(stdout, "%s%#lx", delim, reg);
	}
}

/**
 * printArgs - program that prints all arguments to a syscall
 *
 * @regs: user registers struct containing register values
 *
 * Return: nothing (void)
 */

void printArgs(struct user_regs_struct regs)
{
	printReg(regs, 0, regs.rdi, "");
	printReg(regs, 1, regs.rsi, ", ");
	printReg(regs, 2, regs.rdx, ", ");
	printReg(regs, 3, regs.r10, ", ");
	printReg(regs, 4, regs.r8, ", ");
	printReg(regs, 5, regs.r9, ", ");
}

/**
 * trace - program that traces the execution of a subprocess
 *
 * @child: PID of the subprocess to trace
 *
 * Return: EXIT_SUCCESS on successful tracing
 */

int trace(pid_t child)
{
	int status;
	struct user_regs_struct regs;

	waitpid(child, &status, 0);
	ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_TRACESYSGOOD);
	if (waitSyscall(child) != 0)
		return (EXIT_SUCCESS);

	while (1)
	{
		ptrace(PTRACE_GETREGS, child, 0, &regs);
		fprintf(stdout, "%s(", syscalls_64_g[regs.orig_rax].name);
		printArgs(regs);

		if (waitSyscall(child) != 0)
			break;

		ptrace(PTRACE_GETREGS, child, 0, &regs);
		fprintf(stdout, ") = %#lx\n", (ulong)regs.rax);
	}

	fprintf(stdout, ") = ?\n");
	return (EXIT_SUCCESS);
}


/**
 * main - the entry point of the program
 *
 * @argc: number of command-line arguments
 * @argv: array of command-line argument strings
 * @envp: array of environment variable strings
 *
 * Return: EXIT_FAILURE if failed, EXIT_SUCCESS if successful
 */

int main(int argc, char *argv[], char *envp[])
{
	pid_t child;

	if (argc < 2)
	{
		fprintf(stderr, "%s command [args...]\n", argv[0]);
		return (EXIT_FAILURE);
	}

	child = fork();
	++argv;

	if (child == 0)
	{
		ptrace(PTRACE_TRACEME);
		kill(getpid(), SIGSTOP);
		return (execve(argv[0], argv, envp));
	}
	else
	{
		setbuf(stdout, NULL);
		fprintf(stdout, "execve(%p, %p, %p)", (void *)argv[0],
			(void *)argv, (void *)envp);
		return (trace(child));
	}
}
