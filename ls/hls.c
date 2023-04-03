#include "hls.h"
#include <getopt.h>

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

/* define long options */
	struct option long_options[] = {
		{"long", no_argument, NULL, 'l'},
		{"all", no_argument, NULL, 'a'},
		{"one", no_argument, NULL, '1'},
		{"almost-all", no_argument, NULL, 'A'},
		{NULL, 0, NULL, 0}
	};
/* get options */
	int opt;
	int option_index = 0;

	while ((opt = getopt_long(argc, argv, "al1A", long_options, &option_index)) != -1)
	{
		switch (opt)
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

/* check command line args and call print_args with appropriate parameters */
	if (optind == argc)
	{
		handle_args(".", "NULL", flag_all, flag_long, flag_file, flag_one, flag_A);
		if (flag_long == 0 && flag_one == 0)
		{
			printf("\n");
		}
	}

	else
	{
		while (optind < argc)
		{
			struct stat argbuf;
			char *arg = argv[optind];

			if ((lstat(arg, &argbuf)) == -1)
			{
				printf("./hls: cannot access '%s':\
No such file or directory\n", argv[optind]);
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

				if (optind < argc - 1)
				{
					printf("\n");
				}

				if (flag_long == 0 && flag_one == 0)
				{
					printf("\n");
				}
			}
			optind++;
		}
	}
	return (0);
}
