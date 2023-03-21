#include <stdio.h>
#include <dirent.h>

/**
 * main - Main function
 * Lists the content of the current directory by using hls
 * Return: 0 (success)
 */
int main(void)
{

	DIR *dir;

	/* Directory entry */
	struct dirent *ent;

	/* Open the current working directory */
	dir = opendir(".");
	if (dir != NULL)
	{
/* Loop through all the entries in the directory */
		while ((ent = readdir(dir)) != NULL)
		{
			if (ent->d_name[0] != '.')
				printf("%s\t", ent->d_name);
		}
		printf("\n");
/* Close the directory */
		closedir(dir);
	}
	else
	{
/* Print an error message in case of fail */
		perror("");
		return (1);
	}
	return (0);
}
