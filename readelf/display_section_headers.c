#include "header.h"

void display_section_headers(const char *filename)
{
	FILE *file = fopen(filename, "rb");

	if (file == NULL)
	{
		perror("Error opening file");
		exit(1);
	}

	Elf64_Ehdr elf_header;
	Elf64_Shdr section_header;

	if (fread(&elf_header, sizeof(elf_header), 1, file) != 1)
	{
		perror("Error reading ELF header");
		exit(1);
	}

	fseek(file, elf_header.e_shoff, SEEK_SET);

	printf("There are %d section headers, starting at offset 0x%lx:\n",
	       elf_header.e_shnum, elf_header.e_shoff);
	printf("\nSection Headers:\n");
	printf("  [Nr] Name              Type            Address          Offset\n");

	int i;

	for (i = 0; i < elf_header.e_shnum; i++)
	{
		if (fread(&section_header, sizeof(section_header), 1, file) != 1)
		{
			perror("Error reading section header");
			exit(1);
		}

		printf("  [%2d] %-17s %-15x %-15lx %-15lx\n",
		       i, filename + section_header.sh_name,
		       section_header.sh_type, section_header.sh_addr,
		       section_header.sh_offset);
	}

	fclose(file);
}
