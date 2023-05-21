#ifndef H_HEADER_H
#define H_HEADER_H

#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

typedef struct FileInfo {
    char *programName;
    char *fileName;
    int file_size;
    _Bool elf_type;
    _Bool is32bit;
    _Bool isBigEndian;
    FILE *stream;
    Elf64_Ehdr header;
    Elf64_Shdr *sectionHeaders;
    char *sectionHeaderStringTable;
} FileInfo;

void free_memory(FileInfo *fileInfo);
int get_elf_header(FileInfo *fileInfo);
const char *get_elf_type(Elf64_Half e_type);
const char *get_operating_system_abi(unsigned char osabi);
void handle_errors(char *format, char *errorString, FileInfo *fileInfo);
void init_file_info(FileInfo *fileInfo);
int open_elf_file(FileInfo *fileInfo);
int print_elf_header(FileInfo *fileInfo);
const char *get_machine_name(uint16_t machine);

int getSecHeaders(FILE *file, FileInfo *fileInfo);
int get64bitSecHeaders(FILE *file, FileInfo *fileInfo);
int get32bitSecHeaders(FILE *file, FileInfo *fileInfo);
void bswapElf64_Shdr(Elf64_Shdr *shdr64);
void bswapElf32_Shdr(Elf32_Shdr *shdr32);

int printSecHeaders(FileInfo *fileInfo);

const char *getSecType(Elf64_Word sh_type);
const char *getSecFlags(Elf64_Xword sh_flags);

int getSecHeadStrTab(FileInfo *fileInfo);

#endif /* H_HEADER_H */
