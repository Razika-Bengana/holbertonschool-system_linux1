#include "header.h"

/**
 * init_file_info - Initialize variables of the file
 * @fileInfo: Pointer to the FileInfo structure
 * Return: nothing (void)
 */

void init_file_info(FileInfo *fileInfo)
{
	fileInfo->programName = NULL;
	fileInfo->fileName = NULL;
	fileInfo->elf_type = 0;
	fileInfo->isBigEndian = false;
	fileInfo->is32bit = false;
	fileInfo->file_size = 0;
	fileInfo->stream = NULL;
	memset(&(fileInfo->header), 0, sizeof(Elf64_Ehdr));
}
