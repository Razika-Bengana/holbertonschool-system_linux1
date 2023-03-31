#include "hls.h"

/**
 * handle_print_flags - function that handles the flags passed to the program,
 * and prints the informations of the files and directories in the specified
 * directory
 *
 * @dir_arg: the directory path provided as an argument
 *
 * @dir_entry: a pointer to a dirent struct representing the directory entry
 * to be printed
 *
 * @flag_all: a flag indicating whether or not to print hidden files
 *
 * @flag_long: a flag indicating whether or not to print long-form
 * file/directory
 *
 * @flag_one: a flag indicating whether to print the output
 * in one (or more) column
 *
 * @flag_A: a flag indicating whether to list all files in the directory,
 * (except for . or ..), including hidden files
 *
 * Return: nothing (void)
 */


/* function to check flags and print file/directory info accordingly */
void handle_print_flags(char *dir_arg, struct dirent *dir_entry,
			int flag_all, int flag_long, int flag_one, int flag_A)
{
	if (flag_all == 0 && flag_A == 0)
	{
		if ((dir_entry->d_name[0] == '.'))
		{
			return;
		}
	}

	if (flag_long == 0)
	{
		if (flag_one == 1)
		{
			printf("%s\n", dir_entry->d_name);
		}

		else
		{
			printf("%s ", dir_entry->d_name);
		}
	}

	else
	{
		print_long(dir_arg, dir_entry);
	}
}
