#include "header.h"

void print_elf_header(Elf64_Ehdr *elf_header)
{
	int i;

	printf("ELF Header:\n");
	printf("  Magic:  ");
	for (i = 0; i < EI_NIDENT; ++i)
		printf("%02x ", elf_header->e_ident[i]);
	printf("\n");
	printf("  Class:                             %s\n", elf_header->e_ident[EI_CLASS] == ELFCLASS32 ? "ELF32" : "ELF64");
	printf("  Data:                              %s\n", elf_header->e_ident[EI_DATA] == ELFDATA2LSB ? "2's complement, little endian" : "2's complement, big endian");
	printf("  Version:                           %d (current)\n", elf_header->e_ident[EI_VERSION]);
	printf("  OS/ABI:                            ");
	switch (elf_header->e_ident[EI_OSABI])
	{
	case ELFOSABI_SYSV:
		printf("UNIX - System V\n");
		break;
        case ELFOSABI_HPUX:
		printf("HP-UX\n");
		break;
        case ELFOSABI_NETBSD:
		printf("NetBSD\n");
		break;
        case ELFOSABI_LINUX:
		printf("Linux\n");
		break;
        case ELFOSABI_SOLARIS:
		printf("Solaris\n");
		break;
        case ELFOSABI_AIX:
		printf("AIX\n");
		break;
        case ELFOSABI_IRIX:
		printf("IRIX\n");
		break;
        case ELFOSABI_FREEBSD:
		printf("FreeBSD\n");
		break;
        case ELFOSABI_TRU64:
		printf("Tru64 UNIX\n");
		break;
        case ELFOSABI_MODESTO:
		printf("Novell Modesto\n");
		break;
        case ELFOSABI_OPENBSD:
		printf("OpenBSD\n");
		break;
        case ELFOSABI_ARM_AEABI:
		printf("ARM EABI\n");
		break;
        case ELFOSABI_ARM:
		printf("ARM\n");
		break;
        case ELFOSABI_STANDALONE:
		printf("Standalone (embedded)\n");
		break;
        default:
		printf("<unknown>\n");
		break;
	}
	printf("  ABI Version:                       %d\n", elf_header->e_ident[EI_ABIVERSION]);
	printf("  Type:                              %s\n", elf_header->e_type == ET_REL ? "REL (Relocatable file)" :
	       elf_header->e_type == ET_EXEC ? "EXEC (Executable file)" :
	       elf_header->e_type == ET_DYN ? "DYN (Shared object file)" :
	       elf_header->e_type == ET_CORE ? "CORE (Core file)" :
	       "Unknown");
	printf("  Machine:                           %s\n", elf_header->e_machine == EM_X86_64 ? "Advanced Micro Devices X86-64" :
	       elf_header->e_machine == EM_386 ? "Intel 80386" :
	       elf_header->e_machine == EM_ARM ? "ARM" :
	       elf_header->e_machine == EM_AARCH64 ? "AArch64" :
	       elf_header->e_machine == EM_MIPS ? "MIPS R3000" :
	       elf_header->e_machine == EM_PPC ? "PowerPC" :
	       "Unknown");
	printf("  Version:                           0x%x\n", elf_header->e_version);
	printf("  Entry point address:               0x%lx\n", (unsigned long)elf_header->e_entry);
	printf("  Start of program headers:          %lu (bytes into file)\n", (unsigned long)elf_header->e_phoff);
	printf("  Start of section headers:          %lu (bytes into file)\n", (unsigned long)elf_header->e_shoff);
	printf("  Flags:                             0x%x\n", elf_header->e_flags);
	printf("  Size of this header:               %d (bytes)\n", elf_header->e_ehsize);
	printf("  Size of program headers:           %d (bytes)\n", elf_header->e_phentsize);
	printf("  Number of program headers:         %d\n", elf_header->e_phnum);
	printf("  Size of section headers:           %d (bytes)\n", elf_header->e_shentsize);
	printf("  Number of section headers:         %d\n", elf_header->e_shnum);
	printf("  Section header string table index: %d\n", elf_header->e_shstrndx);
}

int main(int argc, char *argv[])
{
	const char *filename;
	Elf64_Ehdr elf_header;
	FILE *file;
	
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s elf_filename\n", argv[0]);
		return 1;
	}

	filename = argv[1];
	file = fopen(filename, "rb");
	if (!file)
	{
		fprintf(stderr, "Error opening file: %s\n", filename);
		return 1;
	}

	if (fread(&elf_header, sizeof(elf_header), 1, file) != 1)
	{
		fprintf(stderr, "Error reading ELF header\n");
		fclose(file);
		return 1;
	}

	print_elf_header(&elf_header);

	fclose(file);
	return 0;
}
