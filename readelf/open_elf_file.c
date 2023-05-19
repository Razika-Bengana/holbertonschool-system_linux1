#include "header.h"

/**
 * open_elf_file - Opens the file
 * @fileInfo: Pointer to the FileInfo structure
 * Return: 0 (succcess)  or 1 (failure)
 */
int open_elf_file(FileInfo *fileInfo)
{
	char magic4[(EI_NIDENT / 2)];
	struct stat statbuf;

	if (stat(fileInfo->fileName, &statbuf) < 0)
	{
		if (errno == ENOENT)
			handle_errors("%s: No such file\n", NULL, fileInfo);
		else
			handle_errors("Could not locate '%s'. System error message: %s\n",
				      strerror(errno), fileInfo);
		return (1);
	}

	if (!S_ISREG(statbuf.st_mode))
	{
		handle_errors("'%s' is not an ordinary file\n", NULL, fileInfo);
		return (1);
	}

	fileInfo->stream = fopen(fileInfo->fileName, "rb");
	if (fileInfo->stream == NULL)
	{
		handle_errors("Input file '%s' is not readable.\n", NULL, fileInfo);
		return (1);
	}

	if (fread(magic4, (EI_NIDENT / 2), 1, fileInfo->stream) != 1)
	{
		handle_errors("%s: Failed to read file's magic number\n", NULL, fileInfo);
		return (1);
	}

	fileInfo->file_size = statbuf.st_size;
	rewind(fileInfo->stream);

	return (0);
}
