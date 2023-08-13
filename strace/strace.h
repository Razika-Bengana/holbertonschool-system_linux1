#ifndef STRACE_H
#define STRACE_H

#include "syscalls.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/reg.h>
#include <string.h>

/* task 1 + task 2 */
int traceProcess(char *args[], char *env[]);
int waitSyscall(pid_t child);

/* task 3 */
int waitSyscall(pid_t child);
void printReg(struct user_regs_struct regs, int idx, ulong reg, char *delim);
void printArgs(struct user_regs_struct regs);
int trace(pid_t child);


#endif /* STRACE_H */
