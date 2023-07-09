#ifndef HNM_H
#define HNM_H


#include <elf.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


typedef struct nm_state_s
{
	char *exec_name;
	char *f_name;
	FILE *f_stream;
	int f_size;
	bool big_endian;
	bool ELF_32bit;
	Elf64_Ehdr f_header;
	Elf64_Shdr *s_headers;
	Elf64_Shdr *symtab_sh;
	Elf64_Sym *symtab_st;
} nm_state;


/* hnm.c */
/* int main(int argc, char **argv) */


/* hnm_elf_parser.c */
int openELF(nm_state *state);
void errorMsg(char *format, char *err_str, nm_state *state);
void initState(nm_state *state);
void closeState(nm_state *state);


/* hnm_get_file_header.c */
int getFileHeader(nm_state *state);
int get64bitFileHeader(nm_state *state);
int get32bitFileHeader(nm_state *state);
void bswapElf64_Ehdr(Elf64_Ehdr *ehdr64);
void bswapElf32_Ehdr(Elf32_Ehdr *ehdr32);


/* hnm_get_section_headers.c */
int getSectionHeaders(nm_state *state);
int get64bitSectionHeaders(nm_state *state);
int get32bitSectionHeaders(nm_state *state);
void bswapElf64SectionHeader(Elf64_Shdr *shdr64);
void bswapElf32SectionHeader(Elf32_Shdr *shdr32);


/* hnm_get_symbol_tables.c */
int getSymTables(nm_state *state);
int get64bitSymTables(nm_state *state);
int get32bitSymTables(nm_state *state);
void bswapElf64_Sym(Elf64_Sym *sym64);
void bswapElf32_Sym(Elf32_Sym *sym32);

/* hnm_promote_E32Sym_to_E64Sym.c */
void E32SymToE64Sym(Elf32_Sym *Sym32, Elf64_Sym *Sym64);


/* hnm_print_symbol_tables.c */
int printSymTables(nm_state *state);
char getSymNMType(nm_state *state, Elf64_Sym *symbol);
char getSymNMTypeBySec(Elf64_Shdr *section, Elf64_Sym *symbol);


#endif /* HNM_H */
