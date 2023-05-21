#include "header.h"

/**
 * main - displays the information contained in the ELF sections' headers
 * of an ELF file
 * @argc: argument count
 * @argv: the argument vector
 * @env:  the environment variable
 * Return: 0 (success), -1 (failure)
 */
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    display_section_headers(argv[1]);

    return EXIT_SUCCESS;
}
