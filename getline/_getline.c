#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "_getline.h"

#define BUFFER_SIZE 1

char *_getline(const int fd)
{
	static char buffer[BUFFER_SIZE];
	static int pos;
	static int size;
	static int read_count;

	char *line = NULL;
	int i = pos;

	while (1)
	{
/* If we've reached the end of the buffer, read more data from the file */
		if (i == size)
		{
			pos = 0;
			i = 0;
			size = read(fd, buffer, BUFFER_SIZE);
			read_count++;
			if (size <= 0)
			{
/* If there's no more data to read, return NULL */
				return (NULL);
			}
		}

/*
 *If we've found a newline character,
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
/*
 *If we've reached the end of the buffer and there's no newline character,
 * copy the data up to that point into a new string
 */
		if (i == size)
		{
			line = malloc(i - pos + 1);
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
