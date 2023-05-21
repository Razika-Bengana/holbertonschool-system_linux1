#include "header.h"

/**
 * print_elf_header - function that prints the file header
 * @fileInfo: Pointer to the FileInfo structure
 * Return: 0 (success)
 */

int print_elf_header(FileInfo *fileInfo)
{
	int i;

	puts("ELF Header:");
	printf("  Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
		printf("%2.2x ", fileInfo->header.e_ident[i]);
	putchar('\n');
	printf("  Class:                             %s\n",
	       fileInfo->is32bit ? "ELF32" : "ELF64");
	printf("  Data:                              %s, %s endian\n",
	       "2's complement", fileInfo->isBigEndian ? "big" : "little");
	printf("  Version:                           %u%s\n",
	       fileInfo->header.e_ident[EI_VERSION],
	       fileInfo->header.e_ident[EI_VERSION] ==
	       EV_CURRENT ? " (current)" : "");
	printf("  OS/ABI:                            %s\n",
	       get_operating_system_abi(fileInfo->header.e_ident[EI_OSABI]));
	printf("  ABI Version:                       %u\n",
	       fileInfo->header.e_ident[EI_ABIVERSION]);
	printf("  Type:                              %s\n",
	       get_elf_type(fileInfo->header.e_type));
	printf("  Machine:                           %s\n",
	       get_machine_name(fileInfo->header.e_machine));
	printf("  Version:                           0x%x\n",
	       fileInfo->header.e_version);
	printf("  Entry point address:               0x%lx\n",
	       fileInfo->header.e_entry);
	printf("  Start of program headers:          %lu (bytes into file)\n",
	       fileInfo->header.e_phoff);
	printf("  Start of section headers:          %lu (bytes into file)\n",
	       fileInfo->header.e_shoff);
	printf("  Flags:                             0x%x\n",
	       fileInfo->header.e_flags);
	printf("  Size of this header:               %u (bytes)\n",
	       fileInfo->header.e_ehsize);
	printf("  Size of program headers:           %u (bytes)\n",
	       fileInfo->header.e_phentsize);
	printf("  Number of program headers:         %u\n",
	       fileInfo->header.e_phnum);
	printf("  Size of section headers:           %u (bytes)\n",
	       fileInfo->header.e_shentsize);
	printf("  Number of section headers:         %u\n",
	       fileInfo->header.e_shnum);
	printf("  Section header string table index: %u\n",
	       fileInfo->header.e_shstrndx);

	return (0);
}
