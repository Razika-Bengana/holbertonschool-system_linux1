#include "hnm_header.h"

/**
 * getFileHeader - program that reads the ELF file header
 *
 * this function reads the ELF file header from the 'state' structure
 *
 * @state: a pointer to the structure 'nm_state' which contains file data
 * and information for error printing
 *
 * Return: 0 on success, 1 on failure
 */

int getFileHeader(nm_state *state)
{
/* Read the ELF file header's identity array */
	if (fread(state->f_header.e_ident, EI_NIDENT, 1, state->f_stream) != 1)
		return (1);
/* Determine the endianness of the file */
	if (state->f_header.e_ident[EI_DATA] == ELFDATA2MSB)
		state->big_endian = true;
/* Check if the file is a 32-bit ELF file */
	if (state->f_header.e_ident[EI_CLASS] != ELFCLASS64)
		state->ELF_32bit = true;
/* Read the rest of the file header */
	if (state->ELF_32bit)
		return (get32bitFileHeader(state));
	else
		return (get64bitFileHeader(state));
}


/**
 * get64bitFileHeader - program that reads the 64-bit ELF file header
 *
 * this function reads the 64-bit ELF file header and assigns the header values
 * to the corresponding fields in the 'state' structure
 *
 * @state: a pointer to the structure nm_state which contains file data
 * and information for error printing
 *
 * Return: 0 on success, 1 on failure
 */

int get64bitFileHeader(nm_state *state)
{
	Elf64_Ehdr ehdr64;

/* Read the 64-bit ELF file header (excluding the identity array) */
	if (fread(&(ehdr64.e_type), (sizeof(ehdr64) - EI_NIDENT),
		  1, state->f_stream) != 1)
		return (1);
/* Byte swap the header if the file is big endian */
	if (state->big_endian)
		bswapElf64_Ehdr(&ehdr64);

/*
 * Assign the header values to the corresponding fields
 * in the 'state' structure
 */
	state->f_header.e_type      = ehdr64.e_type;
	state->f_header.e_machine   = ehdr64.e_machine;
	state->f_header.e_version   = ehdr64.e_version;
	state->f_header.e_entry     = ehdr64.e_entry;
	state->f_header.e_phoff     = ehdr64.e_phoff;
	state->f_header.e_shoff     = ehdr64.e_shoff;
	state->f_header.e_flags     = ehdr64.e_flags;
	state->f_header.e_ehsize    = ehdr64.e_ehsize;
	state->f_header.e_phentsize = ehdr64.e_phentsize;
	state->f_header.e_phnum     = ehdr64.e_phnum;
	state->f_header.e_shentsize = ehdr64.e_shentsize;
	state->f_header.e_shnum     = ehdr64.e_shnum;
	state->f_header.e_shstrndx  = ehdr64.e_shstrndx;

	return (0);
}


/**
 * get32bitFileHeader - program that reads the 32-bit ELF file header
 *
 * this function reads the 32-bit ELF file header and assigns the header values
 * to the corresponding fields in the 'state' structure
 *
 * @state: a pointer to the structure 'nm_state' which contains file data
 * and information for error printing
 *
 * Return: 0 on success, 1 on failure
 */

int get32bitFileHeader(nm_state *state)
{
	Elf32_Ehdr ehdr32;

/* Read the 32-bit ELF file header (excluding the identity array) */
	if (fread(&(ehdr32.e_type), (sizeof(ehdr32) - EI_NIDENT),
		  1, state->f_stream) != 1)
		return (1);
/* Byte swap the header if the file is big endian */
	if (state->big_endian)
		bswapElf32_Ehdr(&ehdr32);

/*
 * Assign the header values to the corresponding fields
 * in the 'state' structure
 */
	state->f_header.e_type      = (Elf64_Half)ehdr32.e_type;
	state->f_header.e_machine   = (Elf64_Half)ehdr32.e_machine;
	state->f_header.e_version   = (Elf64_Word)ehdr32.e_version;
	state->f_header.e_entry     = (Elf64_Addr)ehdr32.e_entry;
	state->f_header.e_phoff     = (Elf64_Off)ehdr32.e_phoff;
	state->f_header.e_shoff     = (Elf64_Off)ehdr32.e_shoff;
	state->f_header.e_flags     = (Elf64_Word)ehdr32.e_flags;
	state->f_header.e_ehsize    = (Elf64_Half)ehdr32.e_ehsize;
	state->f_header.e_phentsize = (Elf64_Half)ehdr32.e_phentsize;
	state->f_header.e_phnum     = (Elf64_Half)ehdr32.e_phnum;
	state->f_header.e_shentsize = (Elf64_Half)ehdr32.e_shentsize;
	state->f_header.e_shnum     = (Elf64_Half)ehdr32.e_shnum;
	state->f_header.e_shstrndx  = (Elf64_Half)ehdr32.e_shstrndx;

	return (0);
}


/**
 * bswapElf64_Ehdr - program that swaps all the little-endian values
 * in the 'Elf64_Ehdr' structure
 *
 * this function swaps all the little-endian values in the 'Elf64_Ehdr'
 * structure to their big-endian versions
 *
 * @ehdr64: a pointer to the Elf64_Ehdr structure to be byte swapped
 *
 * Return: nothing (void)
 */

void bswapElf64_Ehdr(Elf64_Ehdr *ehdr64)
{
	ehdr64->e_type      = __builtin_bswap16(ehdr64->e_type);
	ehdr64->e_machine   = __builtin_bswap16(ehdr64->e_machine);
	ehdr64->e_version   = __builtin_bswap32(ehdr64->e_version);
	ehdr64->e_entry     = __builtin_bswap64(ehdr64->e_entry);
	ehdr64->e_phoff     = __builtin_bswap64(ehdr64->e_phoff);
	ehdr64->e_shoff     = __builtin_bswap64(ehdr64->e_shoff);
	ehdr64->e_flags     = __builtin_bswap32(ehdr64->e_flags);
	ehdr64->e_ehsize    = __builtin_bswap16(ehdr64->e_ehsize);
	ehdr64->e_phentsize = __builtin_bswap16(ehdr64->e_phentsize);
	ehdr64->e_phnum     = __builtin_bswap16(ehdr64->e_phnum);
	ehdr64->e_shentsize = __builtin_bswap16(ehdr64->e_shentsize);
	ehdr64->e_shnum     = __builtin_bswap16(ehdr64->e_shnum);
	ehdr64->e_shstrndx  = __builtin_bswap16(ehdr64->e_shstrndx);
}


/**
 * bswapElf32_Ehdr - program that swaps all the little-endian values
 * in the 'Elf32_Ehdr' structure
 *
 * this function swaps all the little-endian values in the 'Elf32_Ehdr'
 * structure to their big-endian versions
 *
 * @ehdr32: a pointer to the Elf32_Ehdr structure to be byte swapped
 *
 * Return: nothing (void)
 */

void bswapElf32_Ehdr(Elf32_Ehdr *ehdr32)
{
	ehdr32->e_type      = __builtin_bswap16(ehdr32->e_type);
	ehdr32->e_machine   = __builtin_bswap16(ehdr32->e_machine);
	ehdr32->e_version   = __builtin_bswap32(ehdr32->e_version);
	ehdr32->e_entry     = __builtin_bswap32(ehdr32->e_entry);
	ehdr32->e_phoff     = __builtin_bswap32(ehdr32->e_phoff);
	ehdr32->e_shoff     = __builtin_bswap32(ehdr32->e_shoff);
	ehdr32->e_flags     = __builtin_bswap32(ehdr32->e_flags);
	ehdr32->e_ehsize    = __builtin_bswap16(ehdr32->e_ehsize);
	ehdr32->e_phentsize = __builtin_bswap16(ehdr32->e_phentsize);
	ehdr32->e_phnum     = __builtin_bswap16(ehdr32->e_phnum);
	ehdr32->e_shentsize = __builtin_bswap16(ehdr32->e_shentsize);
	ehdr32->e_shnum     = __builtin_bswap16(ehdr32->e_shnum);
	ehdr32->e_shstrndx  = __builtin_bswap16(ehdr32->e_shstrndx);
}
