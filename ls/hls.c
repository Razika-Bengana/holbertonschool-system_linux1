#include <stdio.h>
#include <dirent.h>

int main(void) {

	DIR *dir;
	struct dirent *ent;

	// Open the current working directory
	if((dir = opendir(".")) != NULL)
	{
		// Loop through all the entries in the directory
		while ((ent = readdir(dir)) != NULL)
		{
			printf("%s\n", ent->d_name);
		}
		// Close the directory
		closedir(dir);
	}
	else
	{
		// Print an error message in case of fail
		perror("");
		return 1;
	}

	return 0;
}
