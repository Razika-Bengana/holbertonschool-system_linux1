# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Werror -Wextra -pedantic

# Target: 0-hreadelf
0-hreadelf: 0-hreadelf.o header.h get_elf_header.o get_machine_name.o handle_errors.o \
            init_file_info.o print_elf_header.o free_memory.o get_elf_type.o \
            get_operating_system_abi.o open_elf_file.o
	$(CC) $(CFLAGS) $^ -o $@

# Target: 1-hreadelf
1-hreadelf: 1-hreadelf.o header.h get_elf_header.o \
            get_machine_name.o handle_errors.o init_file_info.o print_elf_header.o \
            free_memory.o get_elf_type.o get_operating_system_abi.o open_elf_file.o \
	    get_sections_headers.o print_sections_headers.o get_sections_types.o \
	    get_section_header_str_table.c
	$(CC) $(CFLAGS) $^ -o $@

# Rule to compile %.o from %.c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean the build artifacts
clean:
	rm -f *.o 0-hreadelf 1-hreadelf
