#include "hls.h"

/**
 * main - main function;
 * parses command-line arguments, sets flags based on the specific options,
 * and calls the handle_args function to handle each command line arguments
 * @argc: number of command line arguments
 * @argv: array of command-line arguments
 * Return: O if success, -1 if the program fails
 */

/* main function */
int main(int argc, char *argv[])
{

/* initialize flags */
	int flag_long = 0;
	int flag_all = 0;
	int flag_file = 0;
	int flag_one = 0;
	int flag_A = 0;

	int i;
	int j;
/* iterate over each command-line argument */
	for (i = 1; i < argc; i++)
	{
/* check if the argument is an option */
		if (argv[i][0] == '-')
		{
/* iterate over each character in the option string */
			for (j = 1; j < (int)strlen(argv[i]); j++)
			{
				switch (argv[i][j])
				{
				case 'l':
					flag_long = 1;
					break;
				case 'a':
					flag_all = 1;
					break;
				case '1':
					flag_one = 1;
					break;
				case 'A':
					flag_A = 1;
					break;

				default:
					fprintf(stderr, "myls: supports -l, -a, -1 and -A options\n");
					exit(EXIT_FAILURE);
				}
			}
		}
/* if the argument is not an option, handle it as a file/directory name */
		else
		{
			struct stat argbuf;
			char *arg = argv[i];

			if ((lstat(arg, &argbuf)) == -1)
			{
				printf("./hls: cannot access '%s': No such file or directory\n", arg);
			}
			else
			{
				if (S_ISREG(argbuf.st_mode))
				{
					flag_file = 1;
					handle_args(".", arg, flag_all,
						    flag_long, flag_file, flag_one, flag_A);
				}

				if (S_ISDIR(argbuf.st_mode))
				{
					printf("%s:\n", arg);
					handle_args(arg, "NULL", flag_all,
						    flag_long, flag_file, flag_one, flag_A);
				}
				flag_file = 0;

				if (i < argc - 1)
				{
					printf("\n");
				}

				if (flag_long == 0 && flag_one == 0)
				{
					printf("\n");
				}
			}
		}
	}
/* if no command-line arguments were provided, handle the current directory */
	if (argc == 1)
	{
		handle_args(".", "NULL", flag_all, flag_long, flag_file, flag_one, flag_A);
		if (flag_long == 0 && flag_one == 0)
		{
			printf("\n");
		}
	}

	return (0);
}
