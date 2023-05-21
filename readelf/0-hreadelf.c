#include "header.h"

/**
 * main - Entry point of the program
 * @argc: Number of command-line arguments (counter)
 * @argv: Array of command-line arguments (vector)
 * Return: 0 (success), 1 (failure)
 */

int main(int argc, char **argv)
{
	FileInfo fileInfo;
	int flag = 0;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return (1);
	}

	init_file_info(&fileInfo);
	fileInfo.programName = argv[0];
	fileInfo.fileName = argv[1];

	flag = open_elf_file(&fileInfo);
	if (flag == 0)
	{
		flag = get_elf_header(&fileInfo);
		if (flag == 0)
		{
			flag = print_elf_header(&fileInfo);
			if (flag == 0)
                        {
				display_section_headers(fileInfo.fileName);
                        }
		}
		else
		{
			handle_errors("%s: Failed to read file header\n", NULL, &fileInfo);
		}
	}

	free_memory(&fileInfo);
	return (flag);
}
