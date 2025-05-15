#ifndef BUFFER_SIZE
#define BUFFER_SIZE 5
#endif
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>
char	*gnl(int fd)
{
	char	c, *line, *nwline;
	int		rd = 0, capacity = BUFFER_SIZE, i, j;

	if ((rd = read(fd, &c, 1)) <= 0 || BUFFER_SIZE < 1)
		return NULL;

	if (!(line = malloc(capacity + 1)))
		return NULL;

	i = 0;
	while (rd > 0)
	{
		if (i == capacity - 1)
		{
			capacity += BUFFER_SIZE;
			if (!(nwline = malloc(capacity + 1)))
				return free(line), NULL;
			j = -1;
			while (++j < i)
				nwline[j] = line[j];
			free(line);
			line = nwline;
		}
		line[i++] = c;
		if (c == '\n')
			break ;
		rd = read(fd, &c, 1);
	}
	if (rd < 0)
		return free(line), NULL;
	line[i] = '\0';
	printf("%s", line);
	return (line);
}

#include <fcntl.h>
int main()
{
	char	*line;
	int fd = open("x.txt", O_RDONLY);
	line = gnl(fd);
	while (line)
	{
		// printf("%s", line);
		free(line);
		line = gnl(fd);
	}
	free(line);
	return 0;
}