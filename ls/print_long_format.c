#include "hls.h"

/**
 * print_long - function that prints file or directory infos
 * in long format, including permissions and owners/groups
 * @dir_arg: the directory path
 * @dir_entry: the directory entry structure
 * Return: nothing (void)
 */

void print_long(char *dir_arg, struct dirent *dir_entry)
{
	struct stat statbuf;
	char fp[PATH_MAX];
	struct passwd *pw;
	struct group *gid;
	char *time_str;
	time_t t = statbuf.st_mtime;

	sprintf(fp, "%s/%s", dir_arg, dir_entry->d_name);
	if (lstat(fp, &statbuf) == -1)
	{
		perror("lstat");
		return;
	}

/* permission data/nlink */
	printf((S_ISDIR(statbuf.st_mode)) ? "d" : "-");
	printf((statbuf.st_mode & S_IRUSR) ? "r" : "-");
	printf((statbuf.st_mode & S_IWUSR) ? "w" : "-");
	printf((statbuf.st_mode & S_IXUSR) ? "x" : "-");
	printf((statbuf.st_mode & S_IRGRP) ? "r" : "-");
	printf((statbuf.st_mode & S_IWGRP) ? "w" : "-");
	printf((statbuf.st_mode & S_IXGRP) ? "x" : "-");
	printf((statbuf.st_mode & S_IROTH) ? "r" : "-");
	printf((statbuf.st_mode & S_IWOTH) ? "w" : "-");
	printf((statbuf.st_mode & S_IXOTH) ? "x " : "- ");
	printf("%li ", statbuf.st_nlink);

/* group and user data */

	pw = getpwuid(statbuf.st_uid);
	if (pw == NULL)
	{
		perror("getpwuid");
		printf("%d ", statbuf.st_uid);
	}
	else
	{
		printf("%s ", pw->pw_name);
	}

	gid = getgrgid(statbuf.st_gid);
	if (gid == NULL)
	{
		perror("getpwuid");
		printf("%d ", statbuf.st_gid);
	}
	else
	{
		printf("%s ", gid->gr_name);
	}

/* file size */
	printf("%5ld ", statbuf.st_size);

/* timestamp */
	time_str = ctime(&t);
	if (time_str == NULL)
	{
		perror("ctime");
		exit(EXIT_FAILURE);
	}

/* Remove the trailing newline */
	time_str[strcspn(time_str, "\n")] = '\0';
	printf("%s ", time_str);

/* file name */
	printf("%s\n", dir_entry->d_name);
}
