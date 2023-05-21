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
} FileInfo;

int main(int argc, char **argv);
void free_memory(FileInfo *fileInfo);
int get_elf_header(FileInfo *fileInfo);
const char *get_elf_type(Elf64_Half e_type);
const char *get_operating_system_abi(unsigned char osabi);
void handle_errors(char *format, char *errorString, FileInfo *fileInfo);
void init_file_info(FileInfo *fileInfo);
int open_elf_file(FileInfo *fileInfo);
int print_elf_header(FileInfo *fileInfo);
const char *get_machine_name(uint16_t machine);
void display_section_headers(const char *filename);

#endif /* H_HEADER_H */
