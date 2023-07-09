#include "hnm.h"

/**
 * E32SymToE64Sym - program that promotes an Elf32_Sym struct to
 * an Elf64_Sym struct
 *
 * this function takes a pointer to an Elf32_Sym struct and a pointer to a
 * destination Elf64_Sym struct;
 * it promotes the values of the Elf32_Sym struct to their corresponding types
 * in the Elf64_Sym struct;
 * the conversion includes promoting the name, info, other, shndx, value,
 * and size fields
 *
 * @Sym32: a pointer to the Elf32_Sym struct to promote to 64-bit
 * @Sym64: a pointer to the destination Elf64_Sym struct
 *
 * Return: nothing (void)
 */

void E32SymToE64Sym(Elf32_Sym *Sym32, Elf64_Sym *Sym64)
{
	if (!Sym32 || !Sym64)
		return;

	Sym64->st_name  = (Elf64_Word)Sym32->st_name;
	/* 64 and 32 both unsigned char */
	Sym64->st_info  = Sym32->st_info;
	/* 64 and 32 both unsigned char */
	Sym64->st_other = Sym32->st_other;
	Sym64->st_shndx = (Elf64_Section)Sym32->st_shndx;
	Sym64->st_value = (Elf64_Addr)Sym32->st_value;
	Sym64->st_size  = (Elf64_Xword)Sym32->st_size;
}
