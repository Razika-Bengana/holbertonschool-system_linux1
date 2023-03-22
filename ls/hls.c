#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include "hls.h"

/**
 * main - Main function
 * Lists the content of the current directory by using hls
 * @argc: argument count (the number of command line arguments)
 * @argv: argument vector (an array of command line argument strings)
 * Return: 0 (success)
 */

int main(int argc, char *argv[])
{

	DIR *dir;
	struct dirent *ent;

/* Check if there are any arguments */
	if (argc <= 1)
	{

/* No arguments provided, use the current working directory */
		dir = opendir(".");
	}

	else
	{
/* Loop through all the command-line arguments */
		for (int i = 1; i < argc; i++)
		{
/* Check if the argument is a directory */
			dir = opendir(argv[i]);
			if (dir != NULL)
			{
				printf("%s\n", argv[i]);
			}

			else if (errno == ENOTDIR)
			{
/* The argument is not a directory, print the file name */
				printf("%s\t", argv[i]);
				continue;
			}

			else
			{
/* Error opening the directory, print an error message */
				fprintf(stderr, "hls: cannot access '%s': %s\n",
					argv[i], strerror(ENOENT));
				continue;
			}

/* Loop through all the entries in the directory */
			while ((ent = readdir(dir)) != NULL)
			{
				if (ent->d_name[0] != '.')
				{
					printf("%s\t", ent->d_name);
				}
			}

			printf("\n");
		}
	}

/* Close the directory */
		closedir(dir);

		return (EXIT_SUCCESS);
}
