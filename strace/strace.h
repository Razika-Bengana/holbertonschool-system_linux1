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

int startSubprocess(char *args[], char *env[]);
int waitForSyscall(pid_t child);
int traceChild(pid_t child);


#endif /* STRACE_H */
