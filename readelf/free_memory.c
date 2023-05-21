#include "header.h"

/**
 * free_memory - frees allocated memory
 * @fileInfo: pointer to the struct
 * Return: nothing (void)
 */
void free_memory(FileInfo *fileInfo)
{
	if (fileInfo->programName != NULL)
	{
		fileInfo->programName = NULL;
	}
	if (fileInfo->fileName != NULL)
	{
		fileInfo->fileName = NULL;
	}
	if (fileInfo->elf_type != 0)
	{
		fileInfo->elf_type = 0;
	}
}
