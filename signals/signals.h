#ifndef SIGNALS_H
#define SIGNALS_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

typedef void (*sighandler_t)(int);

int handle_signal(void);
void sigint_handler(int signum);
void (*current_handler_signal(void))(int);
int handle_sigaction(void);
void (*current_handler_sigaction(void))(int);
int trace_signal_sender(void);
void sigquit_handler(int signum, siginfo_t *si, void *ucontext);
int pid_exist(pid_t pid);

#endif /* SIGNALS_H */
