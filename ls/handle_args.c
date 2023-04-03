#include "hls.h"

/**
 * my_strcmp - compare two strings character by character
 * @str1: pointer to the first string to compare
 * @str2: pointer to the second string to compare
 * Return: 0 if the strings are equal,
 * a negative integer if the first non-matching character
 * of str1 is less than the corresponding character of str2,
 * a positive integer if the first non-matching character
 * of str1 is greater than the corresponding character of str2
 */


int my_strcmp(const char *str1, const char *str2)
{
/* loop through the strings, comparing each character */
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
/* return the difference between the first non-matching characters */
	return (*(const unsigned char *)str1 - *(const unsigned char *)str2);
}


/**
 * handle_args - function that open/close the directory,
 * handles cmd-line arguments,
 * and passes each directory entry to the flag_handler function
 *
 * @dir_arg: the name of the directory to open and read
 *
 * @file: the name of a specific file to display information for
 *
 * @flag_all: a flag indicating whether all files in the directory should
 * be displayed, including hidden files
 *
 * @flag_long: a flag indicating whether detailed information
 * should be displayed for each file
 *
 * @flag_file: a flag indicating whether only a specific file should
 * be displayed, or if all files in the directory should be displayed
 *
 *@flag_one: a flag indicating whether to print the output
 * in one (or more) column
 *
 * @flag_A: a flag indicating whether to list all files in the directory,
 * (except for . or ..), including hidden files
 *
 * Return: nothing (void)
 */


/* function to handle cmd-line args */
void handle_args(char *dir_arg, char *file, int flag_all,
		 int flag_long, int flag_file, int flag_one, int flag_A)
{

/* open directory */
	DIR *dir = opendir(dir_arg);
	struct dirent *dir_entry;

	if (dir == NULL)
	{
		perror("opendir");
		exit(EXIT_FAILURE);
	}

/* read and print directory/file data */

	errno = 0;

	while ((dir_entry = readdir(dir)) != NULL)
	{

		if (flag_all == 0 && dir_entry->d_name[0] == '.')
			continue;

		if (flag_file == 1)
		{
			if (my_strcmp(dir_entry->d_name, file) == 0)
			{
				handle_print_flags(dir_arg, dir_entry, flag_all,
						   flag_long, flag_one, flag_A);
			}
		}

		else
		{
			handle_print_flags(dir_arg, dir_entry, flag_all,
					   flag_long, flag_one, flag_A);
		}
	}

	if ((dir_entry == NULL) && (errno != 0))
	{
		perror("readdir");
		exit(EXIT_FAILURE);
	}

/* close directory */
	closedir(dir);
}
