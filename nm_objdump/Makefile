# MakeFile

CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic


# task 0 -> nm -p
hnm.o: hnm.c
	$(CC) -c $(CFLAGS) hnm.c

hnm_elf_parser.o: hnm_elf_parser.c
	$(CC) -c $(CFLAGS) hnm_elf_parser.c

hnm_get_file_header.o: hnm_get_file_header.c
	$(CC) -c $(CFLAGS) hnm_get_file_header.c

hnm_get_section_headers.o: hnm_get_section_headers.c
	$(CC) -c $(CFLAGS) hnm_get_section_headers.c

hnm_get_symbol_tables.o: hnm_get_symbol_tables.c
	$(CC) -c $(CFLAGS) hnm_get_symbol_tables.c

hnm_promote_E32Sym_to_E64Sym.o: hnm_promote_E32Sym_to_E64Sym.c
	$(CC) -c $(CFLAGS) hnm_promote_E32Sym_to_E64Sym.c

hnm_print_symbol_tables.o: hnm_print_symbol_tables.c
	$(CC) -c $(CFLAGS) hnm_print_symbol_tables.c

hnm: hnm.h hnm.o hnm_elf_parser.o hnm_get_file_header.o \
	hnm_get_section_headers.o hnm_get_symbol_tables.o \
	hnm_promote_E32Sym_to_E64Sym.o hnm_print_Symbol_tables.o
	$(CC) $(CFLAGS) hnm.o hnm_elf_parser.o hnm_get_file_header.o \
	hnm_get_section_headers.o hnm_get_symbol_tables.o \
	hnm_promote_E32Sym_to_E64Sym.o hnm_print_Symbol_tables.o \
	-o hnm
