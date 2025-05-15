#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif

char	*gnl(int fd)
{
	char c;
	if (BUFFER_SIZE < 1)
		return NULL;

	int rd = read(fd, &c, 1);
	if (rd < 0)
		return (perror("Error"), NULL);
	if (!rd)
		return (NULL);
	char *line = malloc(BUFFER_SIZE + 1);
	if (!line)
		return perror("Error"), NULL;

	int i = 0, capacity = BUFFER_SIZE;
	while (rd)
	{
		if (i == capacity)	// check if i have to conpare with capacity - 1
		{
			capacity += BUFFER_SIZE;
			char *nwline = malloc(capacity + 1);
			if (!nwline)
				return free(line), perror("Error"), NULL;
			int j = -1;
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
	line[i] = '\0';
	return (line);
}

int main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	if (!av[1] || !av[1][0])
		return (1);

	int fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return 1;

	char *line = gnl(fd);
	if (!line)
		return 1;
	while (line)
	{
		printf("%s", line);
		free(line);
		line = gnl(fd);
	}
	free(line); // no ned because it'll be NULL
	close (fd);

	return (0);
}