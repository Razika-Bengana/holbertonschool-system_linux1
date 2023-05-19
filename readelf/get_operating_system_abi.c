#include "header.h"

/**
 * get_operating_system_abi - Convert OS ABI code to string
 * @osabi: OS ABI code
 * Return: String representation of the OS ABI
 */

const char *get_operating_system_abi(unsigned char osabi)
{
	static char buffer[32] = {'\0'};

	switch (osabi)
	{
	case ELFOSABI_NONE:
		return ("UNIX - System V");
        case ELFOSABI_HPUX:
		return ("UNIX - HP-UX");
        case ELFOSABI_NETBSD:
		return ("UNIX - NetBSD");
        case ELFOSABI_GNU:
		return ("UNIX - GNU");
        case ELFOSABI_SOLARIS:
		return ("UNIX - Solaris");
        case ELFOSABI_AIX:
		return ("UNIX - AIX");
        case ELFOSABI_IRIX:
		return ("UNIX - IRIX");
        case ELFOSABI_FREEBSD:
		return ("UNIX - FreeBSD");
        case ELFOSABI_TRU64:
		return ("UNIX - TRU64");
        case ELFOSABI_MODESTO:
		return ("Novell - Modesto");
        case ELFOSABI_OPENBSD:
		return ("UNIX - OpenBSD");
        case ELFOSABI_ARM:
		return ("ARM");
        case ELFOSABI_ARM_AEABI:
		return ("ARM EABI");
        case ELFOSABI_STANDALONE:
		return ("Standalone App");
        default:
		snprintf(buffer, sizeof(buffer), "<unknown: %x>", osabi);
		return (buffer);
	}
}
