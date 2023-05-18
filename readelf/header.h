#ifndef H_HEADER_H
#define H_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <elf.h>

void print_elf_header(Elf64_Ehdr *elf_header);
int main(int argc, char* argv[]);

#endif /* H_HEADER_H */
