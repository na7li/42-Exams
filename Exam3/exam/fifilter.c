#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

/*
pattern is av[1] exactly
get line from stdin
print it after scanning it
*/
char	*ft_strdup(char *str, int *sig)
{
	if (!str)
		return (NULL);

	int i = 0;
	while (str[i])
		i++;

	char *line = malloc(i + 1);
	if (!line)
		return (*sig = 303, perror("Error"), NULL);

	i = -1;
	while (str[++i])
		line[i] = str[i];
	line[i] = '\0';
	return (line);
}

void	printline(char *line, char *av)
{
	int i = 0;
	if (!line || !av)
		return ;
	while (line[i]) {
		int j = 0;
		while (line[i] == av[j] && av[j])
			i++, j++;

		if (!av[j]) {
			j = -1;
			while (av[++j])
				write(1, "*", 1);
		}
		else {
			i = i - j;
			write(1, &line[i++], 1);
		}
	}
	write(1, "\n", 1);
}

char	*getinput(int fd, char *av, int *sig)
{
	int i = 0, j;

	char buff[BUFFER_SIZE], line[100000];

	while (1) {
		int rd = read(fd, buff, BUFFER_SIZE);
		if (rd < 0)
			return (*sig = 404, perror("Error"), NULL);
		if (!rd && !i)
			return (NULL);
		else if (!rd) {
			if (BUFFER_SIZE > 1)
				line[i] = '\0'; // Good practice.
			printline(ft_strdup(line, sig), av);
			return (NULL);
		}

		j = 0;
		while (j < rd) {
			line[i] = buff[j];
			if (buff[j] == '\n')
				break ;
			i++, j++;
		}
		if (buff[j] == '\n')
			break ;
	}
	line[i] = '\0';
	return (ft_strdup(line, sig));
}

int main(int ac, char **av)
{
	if (ac != 2 || BUFFER_SIZE < 1 || !av[1] || !av[1][0])
		return 1;
	int sig = 0;

	char *line = getinput(0, av[1], &sig);
	if (!line && (sig == 404 || sig == 303)) // handle read and malloc error cases. && no input case just EOF;
		return (1);
	else if (!line)
		return (0);
	while (line) {
		printline(line, av[1]);
		free(line);
		line = getinput(0, av[1], &sig);
	}

	if (!line && (sig == 404 || sig == 303)) // handle read and malloc error cases.
		return (1);

	free(line); // no need test leek please

	return (0);
}