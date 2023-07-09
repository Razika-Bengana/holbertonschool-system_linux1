#include "hnm.h"

/**
 * getSectionHeaders - program that reads ELF section headers and stores them
 * in the 'state' structure
 *
 * this function reads the section headers from the ELF file
 * and stores them in the 'state' structure;
 * depending on the ELF class (32-bit or 64-bit), it calls the appropriate
 * function to handle the headers
 *
 * @state: a pointer to the 'nm_state' structure which contains file data
 * and information for error printing
 *
 * Return: 0 on success, 1 on failure
 */

int getSectionHeaders(nm_state *state)
{
	if (state->f_header.e_shoff)
	{
		if (state->ELF_32bit)
			return (get32bitSectionHeaders(state));
		else
			return (get64bitSectionHeaders(state));
	}

	return (0);
}


/**
 * get64bitSectionHeaders - program that reads 64-bit ELF section headers and
 * assigns them to the 'state' structure
 *
 * this function reads the 64-bit ELF section headers from the file and assigns
 * the header values to the corresponding fields in the 'state' structure;
 * it allocates memory to store the section headers and handles byte swapping
 * if the data is in big-endian format;
 *
 * @state: a pointer to the 'nm_state' structure which contains file data
 * and information for error printing
 *
 * Return: 0 on success, 1 on failure
 */

int get64bitSectionHeaders(nm_state *state)
{
	Elf64_Shdr *sectionHeaders = NULL;
	int index;

	sectionHeaders = malloc(sizeof(Elf64_Shdr) * state->f_header.e_shnum);
	if (!sectionHeaders)
		return (1);

	if (fseek(state->f_stream, state->f_header.e_shoff, SEEK_SET) == -1)
		return (1);

	if (fread(sectionHeaders, sizeof(Elf64_Shdr), state->f_header.e_shnum,
		  state->f_stream) != state->f_header.e_shnum)
		return (1);

	if (state->big_endian)
	{
		for (index = 0; index < state->f_header.e_shnum; index++)
			bswapElf64SectionHeader(sectionHeaders + index);
	}

	state->s_headers = sectionHeaders;

	return (0);
}


/**
 * get32bitSectionHeaders - program that reads 32-bit ELF section headers
 * and assigns them to the 'state' structure
 *
 * this function reads the 32-bit ELF section headers from the file and assigns
 * the header values to the corresponding fields in the 'state' structure;
 * it allocates memory to store the section headers and handles byte swapping
 * if the data is in big-endian format;
 * since the 'state' structure holds 64-bit section headers,
 * it promotes the values to 64-bit before assigning them
 *
 * @state: a pointer to the 'nm_state' structure which contains file data
 * and information for error printing
 *
 * Return: 0 on success, 1 on failure
 */

int get32bitSectionHeaders(nm_state *state)
{
	Elf32_Shdr *sectionHeaders32 = NULL;
	Elf64_Shdr *sectionHeaders64 = NULL;
	int index;

	sectionHeaders32 = malloc(sizeof(Elf32_Shdr) * state->f_header.e_shnum);
	sectionHeaders64 = malloc(sizeof(Elf64_Shdr) * state->f_header.e_shnum);

	if (!sectionHeaders32 || !sectionHeaders64)
		return (1);
	if (fseek(state->f_stream, state->f_header.e_shoff, SEEK_SET) == -1)
		return (1);
	if (fread(sectionHeaders32, sizeof(Elf32_Shdr), state->f_header.e_shnum,
		  state->f_stream) != state->f_header.e_shnum)
		return (1);

	if (state->big_endian)
	{
		for (index = 0; index < state->f_header.e_shnum; index++)
			bswapElf32SectionHeader(sectionHeaders32 + index);
	}
	for (index = 0; index < state->f_header.e_shnum; index++)
	{
		Elf32_Shdr *curr32 = sectionHeaders32 + index;
		Elf64_Shdr *curr64 = sectionHeaders64 + index;

		curr64->sh_name = (Elf64_Word)curr32->sh_name;
		curr64->sh_type = (Elf64_Word)curr32->sh_type;
		curr64->sh_flags = (Elf64_Xword)curr32->sh_flags;
		curr64->sh_addr = (Elf64_Addr)curr32->sh_addr;
		curr64->sh_offset = (Elf64_Off)curr32->sh_offset;
		curr64->sh_size = (Elf64_Xword)curr32->sh_size;
		curr64->sh_link = (Elf64_Word)curr32->sh_link;
		curr64->sh_info = (Elf64_Word)curr32->sh_info;
		curr64->sh_addralign = (Elf64_Xword)curr32->sh_addralign;
		curr64->sh_entsize = (Elf64_Xword)curr32->sh_entsize;
	}
	free(sectionHeaders32);
	state->s_headers = sectionHeaders64;

	return (0);
}

/**
 * bswapElf64SectionHeader - program that swaps all the little-endian values
 * in the 'Elf64_Shdr' structure to their big-endian versions
 *
 * this function byte swaps all the little-endian values in the 'Elf64_Shdr'
 * structure to their big-endian versions;
 * It takes a pointer to the structure and modifies its contents in-place
 *
 * @shdr64: a pointer to the Elf64_Shdr structure to be byte swapped
 *
 * Return: nothing (void)
 */

void bswapElf64SectionHeader(Elf64_Shdr *shdr64)
{
	shdr64->sh_name = __builtin_bswap32(shdr64->sh_name);
	shdr64->sh_type = __builtin_bswap32(shdr64->sh_type);
	shdr64->sh_flags = __builtin_bswap64(shdr64->sh_flags);
	shdr64->sh_addr = __builtin_bswap64(shdr64->sh_addr);
	shdr64->sh_offset = __builtin_bswap64(shdr64->sh_offset);
	shdr64->sh_size = __builtin_bswap64(shdr64->sh_size);
	shdr64->sh_link = __builtin_bswap32(shdr64->sh_link);
	shdr64->sh_info = __builtin_bswap32(shdr64->sh_info);
	shdr64->sh_addralign = __builtin_bswap64(shdr64->sh_addralign);
	shdr64->sh_entsize = __builtin_bswap64(shdr64->sh_entsize);
}

/**
 * bswapElf32SectionHeader - program that swaps all little-endian values
 * in the 'Elf32_Shdr' structure to their big-endian versions
 *
 * this function byte swaps all the little-endian values in the 'Elf32_Shdr'
 * structure to their big-endian versions;
 * it takes a pointer to the structure and modifies its contents in-place;
 *
 * @shdr32: a pointer to the Elf32_Shdr structure to be byte swapped
 *
 * Return: nothing (void)
 */

void bswapElf32SectionHeader(Elf32_Shdr *shdr32)
{
	shdr32->sh_name = __builtin_bswap32(shdr32->sh_name);
	shdr32->sh_type = __builtin_bswap32(shdr32->sh_type);
	shdr32->sh_flags = __builtin_bswap32(shdr32->sh_flags);
	shdr32->sh_addr = __builtin_bswap32(shdr32->sh_addr);
	shdr32->sh_offset = __builtin_bswap32(shdr32->sh_offset);
	shdr32->sh_size = __builtin_bswap32(shdr32->sh_size);
	shdr32->sh_link = __builtin_bswap32(shdr32->sh_link);
	shdr32->sh_info = __builtin_bswap32(shdr32->sh_info);
	shdr32->sh_addralign = __builtin_bswap32(shdr32->sh_addralign);
	shdr32->sh_entsize = __builtin_bswap32(shdr32->sh_entsize);
}
