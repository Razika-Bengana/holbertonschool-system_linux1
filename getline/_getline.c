#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "_getline.h"

/* Define the READ_SIZE macro based on whether
 * we want to count calls to read or not
 */
#ifdef COUNT_READ_CALLS
#undef READ_SIZE
#define READ_SIZE 1
#endif

/* Define a macro to override malloc to initialize allocated memory to 0xFF */
#define malloc(size) memset(malloc(size), 0xFF, size)

#define BUFFER_SIZE 1024

char *_getline(const int fd)
{
	static char buffer[BUFFER_SIZE];
	static int pos;
	static int size;
	static int call_count;

	char *line = NULL;
	int i = pos;

	while (1)
	{
/* If we've reached the end of the buffer, read more data from the file */
		if (i == size)
		{
			pos = 0;
			i = 0;
			size = read(fd, buffer, READ_SIZE);
			call_count++;

			if (size <= 0)
			{
				if (line != NULL && i > pos)
				{
					line = realloc(line, i - pos + 1);
					memcpy(line, &buffer[pos], i - pos);
					line[i - pos] = '\0';
					pos = i;
					return (line);
				}
				/* Otherwise, return NULL */
				return (NULL);
			}
		}

/*
 * If we've found a newline character,
 * copy the data up to that point into a new string
 */
		if (buffer[i] == '\n')
		{
			line = malloc(i - pos + 1);
			if (line == NULL)
			{
				return (NULL);
			}
			memcpy(line, &buffer[pos], i - pos);
			line[i - pos] = '\0';
			pos = i + 1;
			break;
		}

		i++;
/* If we've reached the end of the buffer and there's no newline character,
 * copy the data up to that point into a new string
 */
		if (i == size)
		{
			line = realloc(line, i - pos + 1);
			if (line == NULL)
			{
				return (NULL);
			}
			memcpy(line, &buffer[pos], i - pos);
			line[i - pos] = '\0';
			pos = i;
		}
	}

	return (line);
}
