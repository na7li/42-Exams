/*
Assignement name : filter

Expected files : filter.c

Allowed functions : printf, perror, calloc, malloc, realloc, strlen,
					read, free
-------------------------------------------------------------------------

Write a program that will take one argument s.

Your program will then read from stdin and write all the content read in
stdout except that every occurence of s must be replaced by '*' (as many
as the length of s).

For example :

more generally your program must be the equivalent of the shell script
filter.sh present in this directory (you can compare your program with
it)

In case of error during read or a malloc you must write "Error: "
followed by the error message in stderr and return 1.

For example this should work :
$> echo 'abcdefaaaabcdeabcabcdabc' | ./filter abc | cat -e
***defaaa***de******d***$

$> echo 'ababcabababc' | ./a.out ababc | cat -e
*****ab*****$
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 5
#endif

// write with write() instead of printf
// mallo in ft_strdup
char	*ft_strdup(char *s, int *sig)
{
	if (!s[0])
		return NULL;

	int l = strlen(s);
	char	*line = malloc(l + 1);
	if (!line)
		return perror("Error"), *sig = 404, (NULL);
	int i = -1;
	while (s[++i])
		line[i] = s[i];
	line[i] = '\0';
	return line;
}

void	printline(char *line, char *av)
{
	if (!av[0] || !line[0])
		return ;
	int i = 0, j;
	while (line[i])
	{
		j = 0;
		while (line[i] == av[j] && av[j])
			i++, j++;
		if (!av[j])
		{
			while (--j >= 0)
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
	if (!av[0])
		return NULL;
	char	line[100000], buff[BUFFER_SIZE];
	int		rd, i, j;

	i = 0;
	while (1)
	{
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd < 0)
			return perror("Error"), *sig = 404, NULL;
		if (rd == 0 && i == 0)
			return NULL;
		if (rd == 0)
			return line[i] = '\0', printline(ft_strdup(line, sig), av), NULL;
		j = 0;
		while (j < rd) {
			if (buff[j] == '\n')
				break ;
			line[i] = buff[j];
			i++, j++;
		}
		if (buff[j] == '\n')
			break ;
	}
	line[i] = '\0';
	return (ft_strdup(line, sig));
}

int	main(int ac, char **av)
{
	if (ac != 2 || BUFFER_SIZE < 1 || !av[1] || !av[1][0])
		return 0;

	char	*line;
	int		sig = 0;
	// getinput()
	line = getinput(0, av[1], &sig);
	if (!line && sig == 404)
		return (1);
	if (!line && sig == 0)
		return (0);

	// printline()
	while (line)
	{
		printline(line, av[1]);
		free(line);
		line = getinput(0, av[1], &sig);
	}
	free(line);
	if (!line && sig == 404)
		return (1);
	return (0);
}