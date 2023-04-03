#ifndef HLS_H
#define HLS_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
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
int my_strcmp(const char *str1, const char *str2);
void handle_args(char *dir_arg, char *file, int flag_all, int flag_long,
		 int flag_file, int flag_one, int flag_A);
size_t my_str_len_until(const char *str, char c);
#endif /* HLS_H */
