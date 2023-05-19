#include "header.h"

/**
 * get_elf_header - Read and parse the file headers
 * @fileInfo: Pointer to the FileInfo structure
 * Return: 0 (success), 1 (failure)
 */

int get_elf_header(FileInfo *fileInfo)
{
	if (fread(fileInfo->header.e_ident, EI_NIDENT, 1, fileInfo->stream) != 1)
		return (1);

	if (fileInfo->header.e_ident[EI_DATA] == ELFDATA2MSB)
		fileInfo->isBigEndian = true;

	if (fileInfo->header.e_ident[EI_CLASS] != ELFCLASS64)
		fileInfo->is32bit = true;

	if (fileInfo->is32bit)
	{
		Elf32_Ehdr ehdr32;

		if (fread(&(ehdr32.e_type), (sizeof(ehdr32) - EI_NIDENT), 1,
			  fileInfo->stream) != 1)
			return (1);

		fileInfo->header.e_type      = (Elf64_Half)ehdr32.e_type;
		fileInfo->header.e_machine   = (Elf64_Half)ehdr32.e_machine;
		fileInfo->header.e_version   = (Elf64_Word)ehdr32.e_version;
		fileInfo->header.e_entry     = (Elf64_Addr)ehdr32.e_entry;
		fileInfo->header.e_phoff     = (Elf64_Off)ehdr32.e_phoff;
		fileInfo->header.e_shoff     = (Elf64_Off)ehdr32.e_shoff;
		fileInfo->header.e_flags     = (Elf64_Word)ehdr32.e_flags;
		fileInfo->header.e_ehsize    = (Elf64_Half)ehdr32.e_ehsize;
		fileInfo->header.e_phentsize = (Elf64_Half)ehdr32.e_phentsize;
		fileInfo->header.e_phnum     = (Elf64_Half)ehdr32.e_phnum;
		fileInfo->header.e_shentsize = (Elf64_Half)ehdr32.e_shentsize;
		fileInfo->header.e_shnum     = (Elf64_Half)ehdr32.e_shnum;
		fileInfo->header.e_shstrndx  = (Elf64_Half)ehdr32.e_shstrndx;
	}
	else
	{
		Elf64_Ehdr ehdr64;

		if (fread(&(ehdr64.e_type), (sizeof(ehdr64) - EI_NIDENT), 1,
			  fileInfo->stream) != 1)
			return (1);

		fileInfo->header.e_type      = ehdr64.e_type;
		fileInfo->header.e_machine   = ehdr64.e_machine;
		fileInfo->header.e_version   = ehdr64.e_version;
		fileInfo->header.e_entry     = ehdr64.e_entry;
		fileInfo->header.e_phoff     = ehdr64.e_phoff;
		fileInfo->header.e_shoff     = ehdr64.e_shoff;
		fileInfo->header.e_flags     = ehdr64.e_flags;
		fileInfo->header.e_ehsize    = ehdr64.e_ehsize;
		fileInfo->header.e_phentsize = ehdr64.e_phentsize;
		fileInfo->header.e_phnum     = ehdr64.e_phnum;
		fileInfo->header.e_shentsize = ehdr64.e_shentsize;
		fileInfo->header.e_shnum     = ehdr64.e_shnum;
		fileInfo->header.e_shstrndx  = ehdr64.e_shstrndx;
	}

	return (0);
}
