# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Werror -Wextra -pedantic

# Source files
SRCS = free_memory.c get_elf_header.c \
        get_elf_type.c get_operating_system_abi.c \
        handle_errors.c header.h init_file_info.c \
        open_elf_file.c print_elf_header.c get_machine_name.c

# Object files
OBJS = $(SRCS:.c=.o)

# Rule to compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Targets
0-hreadelf: 0-hreadelf.o $(OBJS)
	$(CC) $(CFLAGS) 0-hreadelf.o $(OBJS) -o 0-hreadelf

1-hreadelf: 1-hreadelf.o $(OBJS)
	$(CC) $(CFLAGS) 1-hreadelf.o $(OBJS) -o 1-hreadelf

2-hreadelf: 2-hreadelf.o $(OBJS)
	$(CC) $(CFLAGS) 2-hreadelf.o $(OBJS) -o 2-hreadelf

# Rule to clean the build artifacts
clean:
	rm -f $(OBJS) 0-hreadelf 1-hreadelf 2-hreadelf
