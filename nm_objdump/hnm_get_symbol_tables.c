#include "hnm.h"

/**
 * getSymTables - program that selects the function to get symbol tables
 * based on the ELF configuration (32-bit or 64-bit)
 *
 * This function determines the ELF configuration (32-bit or 64-bit)
 * in the 'state' structure and calls the appropriate function to handle
 * the symbol tables.
 *
 * @state: a pointer to the 'nm_state' structure which contains file data and
 * information for error printing
 *
 * Return: 0 on success, 1 on failure
 */

int getSymTables(nm_state *state)
{
	if (state->ELF_32bit)
		return (get32bitSymTables(state));
	else
		return (get64bitSymTables(state));
}


/**
 * get64bitSymTables - program that reads the ELF file and stores
 * the 64-bit symbol tables in the 'state' structure
 *
 * This function reads the 64-bit symbol tables from the ELF file and assigns
 * them to the corresponding fields in the 'state' structure.
 * It allocates memory to store the symbol tables and handles byte swapping
 * if the data is in big-endian format.
 *
 * @state: a pointer to the 'nm_state' structure which contains file data and
 * information for error printing
 *
 * Return: 0 on success, 1 on failure
 */

int get64bitSymTables(nm_state *state)
{
	Elf64_Sym *sym_tab = NULL;
	Elf64_Shdr *section = NULL;
	unsigned int section_index, symbol_index, num_symbols;

	for (section_index = 0; section_index < state->f_header.e_shnum;
	     section_index++)
	{
		section = state->s_headers + section_index;
		if (section->sh_type == SHT_SYMTAB)
		{
			state->symtab_sh = section;

			num_symbols = section->sh_size / section->sh_entsize;
			sym_tab = malloc(sizeof(Elf64_Sym) * num_symbols);
			if (!sym_tab)
				return (1);

			if (fseek(state->f_stream, section->sh_offset,
				  SEEK_SET) == -1)
				return (1);

			if (fread(sym_tab, sizeof(Elf64_Sym), num_symbols,
				  state->f_stream) != num_symbols)
				return (1);

			if (state->big_endian)
			{
				for (symbol_index = 0;
				     symbol_index < num_symbols; symbol_index++)
					bswapElf64_Sym(sym_tab + symbol_index);
			}

			state->symtab_st = sym_tab;
		}
	}

	return (0);
}


/**
 * get32bitSymTables - program that reads the ELF file and stores the 32-bit
 * symbol tables in the 'state' structure
 *
 * This function reads the 32-bit symbol tables from the ELF file and assigns
 * them to the corresponding fields in the 'state' structure.
 * It allocates memory to store the symbol tables and handles byte swapping
 * if the data is in big-endian format.
 * Since the 'state' structure holds 64-bit symbol tables, it promotes the
 * values from 32-bit to 64-bit before assigning them.
 *
 * @state: a pointer to the 'nm_state' structure which contains file data
 * and information for error printing
 *
 * Return: 0 on success, 1 on failure
 */

int get32bitSymTables(nm_state *state)
{
	Elf32_Sym *sym_tab32 = NULL;
	Elf64_Sym *sym_tab64 = NULL;
	Elf64_Shdr *section = NULL;
	unsigned int section_index, symbol_index, num_symbols;

	for (section_index = 0; section_index < state->f_header.e_shnum;
	     section_index++)
	{
		section = state->s_headers + section_index;
		if (section->sh_type == SHT_SYMTAB)
		{
			state->symtab_sh = section;

			num_symbols = section->sh_size / section->sh_entsize;
			sym_tab32 = malloc(sizeof(Elf32_Sym) * num_symbols);
			sym_tab64 = malloc(sizeof(Elf64_Sym) * num_symbols);
			if (!sym_tab32 || !sym_tab64)
				return (1);
			if (fseek(state->f_stream, section->sh_offset,
				  SEEK_SET) == -1)
				return (1);
			if (fread(sym_tab32, sizeof(Elf32_Sym), num_symbols,
				  state->f_stream) != num_symbols)
				return (1);

			if (state->big_endian)
			{
				for (symbol_index = 0;
				     symbol_index < num_symbols; symbol_index++)
					bswapElf32_Sym(sym_tab32 + symbol_index);
			}
			for (symbol_index = 0; symbol_index < num_symbols;
			     symbol_index++)
				E32SymToE64Sym(sym_tab32 + symbol_index,
					       sym_tab64 + symbol_index);
			free(sym_tab32);
			state->symtab_st = sym_tab64;
		}
	}
	return (0);
}


/**
 * bswapElf64_Sym - program that swaps all little-endian values in the
 * 'Elf64_Sym' structure to their big-endian versions
 *
 * This function byte swaps all the little-endian values in the 'Elf64_Sym'
 * structure to their big-endian versions;
 * it takes a pointer to the structure and modifies its contents in-place;
 *
 * @sym64: a pointer to the Elf64_Sym structure to be byte swapped
 *
 * Return: nothing (void)
 */

void bswapElf64_Sym(Elf64_Sym *sym64)
{
	sym64->st_name   = __builtin_bswap32(sym64->st_name);
	sym64->st_shndx  = __builtin_bswap16(sym64->st_shndx);
	sym64->st_value = __builtin_bswap64(sym64->st_value);
	sym64->st_size  = __builtin_bswap64(sym64->st_size);
}


/**
 * bswapElf32_Sym - program that swaps all little-endian values in the
 * 'Elf32_Sym' structure to their big-endian versions
 *
 * This function byte swaps all the little-endian values in the 'Elf32_Sym'
 * structure to their big-endian versions;
 * it takes a pointer to the structure and modifies its contents in-place;
 *
 * @sym32: a pointer to the 'Elf32_Sym' structure to be byte swapped
 *
 * Return: nothing (void)
 */

void bswapElf32_Sym(Elf32_Sym *sym32)
{

	sym32->st_name   = __builtin_bswap32(sym32->st_name);
	sym32->st_value = __builtin_bswap32(sym32->st_value);
	sym32->st_size  = __builtin_bswap32(sym32->st_size);
	sym32->st_shndx  = __builtin_bswap16(sym32->st_shndx);

}
