#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
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

	/* Check if a directory was specified as a command-line argument */
	if (argc == 2)
	{
		/* Open the specified directory */
		dir = opendir(argv[1]);
		if (dir == NULL)
		{
			fprintf(stderr, "Cannot open directory: %s\n", argv[1]);
			return (EXIT_FAILURE);
		}
	}
	else
	{
		/* Open the current working directory */
		dir = opendir(".");
		if (dir == NULL)
		{
			fprintf(stderr, "Cannot open directory\n");
			return (EXIT_FAILURE);
		}
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

	/* Close the directory */
	closedir(dir);

	return (EXIT_SUCCESS);
}
