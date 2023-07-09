#include "hnm.h"

/**
 * main - entry point to hnm
 *
 * the main function processes each file specified as command-line arguments
 * or processes the default file "a.out" if no arguments are provide;
 * it iterates through the files, calls the necessary functions to retrieve and
 * print information about each file, and returns the appropriate exit code
 *
 * @argc: command line arg count
 * @argv: command line arg array
 *
 * Return: 0 on success, 1 on failure
 */

int main(int argc, char **argv)
{
	char *default_args[] = {"a.out"};
	char **args = argc > 1 ? argv + 1 : default_args;
	nm_state state;
	int i, retval, ac = argc > 1 ? argc - 1 : 1;
/* nm takes multiple files as args */
/* any failure for a single file sets exit code of 1 for entire loop */
	for (i = 0, retval = 0; i < ac; i++)
	{
		initState(&state);
		state.exec_name = argv[0];
		state.f_name = args[i];
/* Open the ELF file */
		if (openELF(&state) == 0)
		{
/* Retrieve the file header */
			if (getFileHeader(&state) == 0)
			{
/* Retrieve and print section headers, symbol tables, and symbols */
				if (!(getSectionHeaders(&state) == 0 &&
				      getSymTables(&state) == 0 &&
				      printSymTables(&state) == 0))
/* Set exit code to 1 if any file processing fails */
					retval = 1;
			}
			else
			{
				errorMsg("%s: File format not recognized\n",
					 NULL, &state);
				retval = 1;
			}
		}
		else
			retval = 1; /* Failed to open the file */
		closeState(&state); /* Close the program state */
	}

	return (retval);
}
