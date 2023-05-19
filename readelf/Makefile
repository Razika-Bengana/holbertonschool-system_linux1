# Target executable name
TARGET = 0-hreadelf

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Werror -Wextra -pedantic

# Source files
SRCS = $(TARGET).c free_memory.c get_elf_header.c \
	get_elf_type.c get_operating_system_abi.c \
	handle_errors.c  header.h  init_file_info.c \
	open_elf_file.c  print_elf_header.c get_machine_name.c

# Object files
OBJS = $(SRCS:.c=.o)

# Build the target executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(TARGET)

# Rule to compile each source file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for "all" target
all: $(TARGET)

# Rule to clean the build artifacts
clean:
	rm -f $(OBJS) $(TARGET)
