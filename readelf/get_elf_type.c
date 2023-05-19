#include "header.h"

/**
 * get_elf_type - Convert ELF type code to string
 * @e_type: ELF type code
 * Return: String representation of the ELF type
 */
const char *get_elf_type(Elf64_Half e_type)
{
	static char buffer[32] = {'\0'};

	switch (e_type)
	{
        case 1:
		return ("REL (Relocatable file)");
        case 2:
		return ("EXEC (Executable file)");
        case 3:
		return ("DYN (Shared object file)");
        case 4:
		return ("CORE");
        default:
		snprintf(buffer, sizeof(buffer), "<unknown: %x>", e_type);
		return (buffer);
	}
}
