#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

/**
 * print_directory - Lists the contents of a directory or file
 * @path: The path to the directory or file
 * Return: 0 (success)
 */

int print_directory(char *path)
{
	DIR *dir;
	struct dirent *ent;

	/* Open the file or directory */
	dir = opendir(path);
	if (dir == NULL)
	{
		/* Error occurred opening the file or directory */
		fprintf(stderr, "%s: cannot access '%s': %s\n",
			__func__, path, strerror(ENOENT));
		return (EXIT_FAILURE);
	}

	/* Print the directory name */
	printf("%s:\n", path);

	/* Print the directory contents */
	while ((ent = readdir(dir)) != NULL)
	{
		if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
		{
			printf("%s\n", ent->d_name);
		}
	}

	closedir(dir);

	return (EXIT_SUCCESS);
}


/**
 * list_files - Lists the contents of one or more directories or files
 * specified as command line arguments
 * @argc: argument count (the number of command line arguments)
 * @argv: argument vector (an array of command line argument strings)
 * Return: 0 (success)
 */

int list_files(int argc, char *argv[])
{
	char cwd[1024];
	char *dir_path;

/* If no arguments were passed, print the contents of the current directory */
	if (argc == 1)
	{
		getcwd(cwd, sizeof(cwd));
		dir_path = cwd;
	}
	else
	{
/* Construct the full path based on the directory name provided */
		getcwd(cwd, sizeof(cwd));
		dir_path = malloc(strlen(cwd) + strlen(argv[1]) + 2);
		snprintf(dir_path, strlen(cwd) + strlen(argv[1]) + 2, "%s/%s", cwd, argv[1]);
	}

/* Print the contents of the directory */
	print_directory(dir_path);

/* Free the allocated memory */
	if (argc > 1)
	{
		free(dir_path);
	}

	return (EXIT_SUCCESS);
}
