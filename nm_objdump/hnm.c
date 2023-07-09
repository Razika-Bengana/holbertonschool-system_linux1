#include "hnm_header.h"

/**
 * processFile - program that processes a single file using the hnm program
 *
 * this function initializes the program state, sets the executable name and
 * the file name,then opens the ELF file;
 * if the file is opened successfully, it retrieves the file header;
 * if the file header is retrieved successfully, it prints the file name, and
 * retrieves also the section headers, symbol tables, and prints the symbol
 * tables;
 * finally, it closes the program state
 *
 * @file_name: name of the file to process
 *
 * Return: 0 on success, or 1 on failure
 */

int processFile(const char *file_name)
{
	nm_state state;

	initState(&state);
	state.exec_name = "hnm";
	state.f_name = (char *)file_name;

	if (openELF(&state) == 0)
	{
		if (getFileHeader(&state) == 0)
		{
			printf("\n%s:\n", file_name);
			if (getSectionHeaders(&state) == 0 &&
			    getSymTables(&state) == 0 &&
			    printSymTables(&state) == 0)
			{
				closeState(&state);
				return (0);
			}
		}

		else
		{
			errorMsg("%s: File format not recognized\n", NULL,
				 &state);
		}
	}

	closeState(&state);
	return (1);
}

/**
 * main - entry point to the hnm program
 *
 * the main function processes each file specified as command-line arguments,
 * or processes the default file "a.out" if no arguments are provided;
 * it calls the processFile function for each file and checks
 * the return values;
 *
 * @argc: command line argument count
 * @argv: command line argument array
 *
 * Return: 0 on success, 1 on failure
 */

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			if (processFile(argv[i]) != 0)
			{
/* Return failure if any file processing fails */
				return (1);
			}
		}
	}

	else
	{
/* No files provided, process the default file */
		if (processFile("a.out") != 0)
		{
/* Return failure if default file processing fails */
			return (1);
		}
	}
/* Return success if all files were processed successfully */
	return (0);
}
