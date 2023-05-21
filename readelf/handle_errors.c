#include "header.h"

/**
 * handle_errors - Function that handles errors
 * @format: Error format string
 * @errorString: Error string
 * @fileInfo: Pointer to the FileInfo structure
 * Return: nothing (void)
 */
void handle_errors(char *format, char *errorString, FileInfo *fileInfo)
{
	fprintf(stderr, "%s: Error: ", fileInfo->programName);
	if (errorString == NULL)
		fprintf(stderr, format, fileInfo->fileName);
	else
		fprintf(stderr, format, fileInfo->fileName, errorString);
}
