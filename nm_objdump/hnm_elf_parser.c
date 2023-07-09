#include "hnm.h"


/**
 * openELF - program that attempts to open an ELF file for parsing and printing
 *
 * this function takes a pointer to the nm_state struct and attempts to open
 * the specified ELF file;
 * it performs various checks on the file, including checking its existence,
 * type, size, and magic number;
 * if the file passes all the checks, it is opened in binary mode for reading;
 * if any errors occur during the process, appropriate error messages
 * are displayed
 *
 * @state: a pointer to the nm_state struct containing file data and error info
 *
 * Return: 0 on success, 1 on failure
 */

int openELF(nm_state *state)
{
	struct stat statbuf;
	char magic[(EI_NIDENT / 2)];

	errno = 0;
	if (stat(state->f_name, &statbuf) < 0)
	{
		if (errno == ENOENT)
			errorMsg("'%s': No such file\n", NULL, state);
		else
			errorMsg("%s: %s\n", strerror(errno), state);
		return (1);
	}
	if (!S_ISREG(statbuf.st_mode))
	{
		errorMsg("Warning: '%s' is not an ordinary file\n",
			 NULL, state);
		return (1);
	}
	if (statbuf.st_size == 0)
		return (1);
	state->f_size = statbuf.st_size;

	state->f_stream = fopen(state->f_name, "rb");
	if (state->f_stream == NULL)
	{
		errorMsg("%s: %s\n", strerror(errno), state);
		return (1);
	}
	if (fread(magic, (EI_NIDENT / 2), 1, state->f_stream) != 1 ||
	    memcmp(ELFMAG, magic, SELFMAG) != 0)
	{
		errorMsg("%s: File format not recognized\n",
			 NULL, state);
		return (1);
	}
	rewind(state->f_stream);

	return (0);
}


/**
 * errorMsg - program that formats and prints error messages
 *
 * this function takes a format string, an optional error string, and a pointer
 * to the nm_state struct;
 * it formats the error message using the provided format string and prints it
 * to the standard error stream;
 * if an error string is provided, it is included in the message;
 * the function is used to display various error messages during the execution
 * of the program
 *
 * @format: format string for the error message
 * @err_str: optional second string containing additional error info
 * @state: a pointer to the nm_state struct containing file data and error info
 *
 * Return: nothing (void)
 */

void errorMsg(char *format, char *err_str, nm_state *state)
{
	fprintf(stderr, "%s: ", state->exec_name);
	if (err_str == NULL)
		fprintf(stderr, format, state->f_name);
	else
		fprintf(stderr, format, state->f_name, err_str);
}


/**
 * initState - program that initializes the nm_state struct
 *
 * this function takes a pointer to the nm_state struct and initializes
 * its members to their initial values;
 * it sets the executable name, file stream, file size, and other fields
 * to their default values;
 * the function uses the memset function to set all the bytes
 * in the nm_state struct to zero
 *
 * @state: a pointer to the nm_state struct to be initialized
 *
 * Return: nothing (void)
 */

void initState(nm_state *state)
{
	state->exec_name = NULL;
	state->f_stream = NULL;
	state->f_size = 0;
	state->big_endian = false;
	state->ELF_32bit = false;
	memset(&(state->f_header), 0, sizeof(Elf64_Ehdr));
	state->s_headers = NULL;
	state->symtab_sh = NULL;
	state->symtab_st = NULL;
}


/**
 * closeState - program that closes the file stream and frees allocated memory
 *
 * this function takes a pointer to the nm_state struct and performs
 * cleanup operations;
 * it closes the file stream if it is open and frees the allocated memory
 * for the section headers and symbol tables;
 * the function is called at the end of the program execution
 * to ensure that all resources are properly released
 *
 * @state: a pointer to the nm_state struct containing file data and error info
 *
 * Return: nothing (void)
 */

void closeState(nm_state *state)
{
	if (state->f_stream != NULL)
		fclose(state->f_stream);

	if (state->s_headers != NULL)
		free(state->s_headers);

	if (state->symtab_st != NULL)
		free(state->symtab_st);
}
