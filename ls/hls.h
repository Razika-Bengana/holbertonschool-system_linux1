#ifndef HLS_H
#define HLS_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>
#include <libgen.h>
#include <sys/types.h>
#include <grp.h>

int main(int argc, char *argv[]);
void print_long(char *dir_arg, struct dirent *dir_entry);
void handle_print_flags(char *dir_arg, struct dirent *dir_entry, int flag_all,
			int flag_long, int flag_one, int flag_A);
void handle_args(char *dir_arg, char *file, int flag_all, int flag_long,
		 int flag_file, int flag_one, int flag_A);

#endif /* HLS_H */
