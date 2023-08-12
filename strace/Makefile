CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic

all: strace_0

# task 0
0_strace.o: 0_strace.c
	$(CC) -c $(CFLAGS) 0_strace.c

strace_0: syscalls.h 0_strace.o
	$(CC) $(CFLAGS) syscalls.h 0_strace.o -o strace_0


# task 1
1_strace.o: 1_strace.c
	$(CC) -c $(CFLAGS) 1_strace.c

strace_1: syscalls.h 1_strace.o
	$(CC) $(CFLAGS) syscalls.h 1_strace.o -o strace_1


clean:
	rm -f strace_0
