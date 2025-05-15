/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPfilter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:08:12 by mnahli            #+#    #+#             */
/*   Updated: 2025/05/14 10:19:20 by mnahli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 13
#endif

#include <stdio.h>

char	*ft_strdup(char *str)
{
	char	*line;
	int		i;

	if (!str)
		return (NULL);
	line = malloc(strlen(str) + 1);
	if (!line)
		return (perror("Error"), NULL);
	i = -1;
	while (str[++i])
	{
		line[i] = str[i];
	}
	line[i] = '\0';
	return (line);
}

void	printline(char *line, char *av)
{
	int i = 0, j;

	while (line[i])
	{
		j = 0;
		while (line[i] == av[j] && av[j])
			i++, j++;
		if (av[j] == '\0') {
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

char	*getinput(int fd, char *av)
{
	int rd, i, j;
	char buff[BUFFER_SIZE], line[100000];

	i = 0;
	while (1)
	{
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd < 0)
			return (perror("Error"), NULL);
		else if (!rd) {
			printline(ft_strdup(line), av);
			return (NULL);
		}
		j = 0;
		while (j < rd)
		{
			if (buff[j] == '\n')
				break ;
			line[i] = buff[j];
			i++, j++;
		}
		line[i] = '\0'; // overwriten in line[i] = buff[j];
		if (buff[j] == '\n') {
			break ;
		}
	}
	return (ft_strdup(line));
}

int main(int ac, char **av)
{
	if (ac != 2 || BUFFER_SIZE < 1 || !av[1] || !av[1][0])
		return (1);
	char *line;
	if (!(line = getinput(0, av[1])))
		return (1);
	while (line) {
		printline(line, av[1]);
		free(line);
		line = getinput(0, av[1]);
	}
	return (0);
}

/**    TOP VERSION    **/
// #ifndef BUFFER_SIZE
// #define BUFFER_SIZE 5
// #endif
// #include <stdio.h>
// #include <string.h>
// #include <unistd.h>
// #include <stdlib.h>


// char	*ft_strdup(char *s, int *signal)
// {
// 	int i = 0;
// 	if (!s)
// 		return NULL;
// 	while (s[i])
// 		i++;
// 	char *line = malloc(i+1);
// 	if (!line) {
// 		*signal = 404;
// 		return perror("Error"), NULL;
// 	}

// 	i = 0;
// 	while (s[i])
// 	{
// 		line[i] = s[i];
// 		i++;
// 	}
// 	line[i] = '\0';
// 	return (line);
// }

// void	printline(char *line, char *av)
// {
// 	int i = 0;

// 	if (!line || !av)
// 		return ;

// 	while (line[i])
// 	{
// 		int j = 0;
// 		while (line[i] == av[j] && av[j])
// 			i++, j++;
// 		if (!av[j])
// 		{
// 			j = -1;
// 			while (av[++j])
// 				write(1, "*", 1);
// 		}
// 		else {
// 			i = i - j;
// 			write(1, &line[i++], 1);
// 		}
// 	}
// 	write(1, "\n", 1);
// }

// char	*getinput(int fd, char *av, int *signal)
// {
// 	int rd, i, j;
// 	char	buff[BUFFER_SIZE], line[100000];

// 	i = 0;
// 	while (1)
// 	{	rd = read(fd, buff, BUFFER_SIZE);
// 		if (rd < 0) {
// 			*signal = 606;
// 			return (perror("Error"), NULL);
// 		}
// 		if (rd == 0 && i == 0)
// 			return *signal = 0, NULL;
// 		if (rd == 0)
// 		{
// 			line[i] = '\0';
// 			printline(ft_strdup(line, signal), av);
// 			return (NULL);
// 		}
// 		j = 0;
// 		while (j < rd)
// 		{
// 			line[i] = buff[j];
// 			if (buff[j] == '\n')
// 				break;
// 			i++, j++;
// 		}
// 		if (buff[j] == '\n')
// 			break;
// 	}
// 	line[i] = '\0';
// 	return (ft_strdup(line, signal));
// }

// int main(int ac, char **av)
// {
// 	if (ac != 2 || BUFFER_SIZE < 1)
// 	return 1;
// 	if (!av[1] || !av[1][0])
// 		return 1;
// 	int signal = 301;
// 	char *line = getinput(0, av[1], &signal);
// 	if (!line && (signal == 404 || signal == 606))
// 		return 1;
// 	if (!line || signal == 0)
// 		return 0;

// 	while (line)
// 	{
// 		printline(line, av[1]);
// 		free(line);
// 		line = getinput(0, av[1], &signal);
// 	}
// 	if (!line && (signal == 404 || signal == 606))
// 		return 1;
// 	free(line);
// 	return 0;
// }
/**  END TOP VERSION  **/

// void	printline(char *line, char *av)
// {
// 	int	i = 0, j;

// 	i = 0, j = 0;
// 	if (!line || !av)
// 		return ;
// 	while (line[i])
// 	{
// 		j = 0;
// 		while (line[i] == av[j] && av[j])
// 			i++, j++;
// 		if (!av[j])
// 		{
// 			j = -1;
// 			while (av[++j])
// 				write(1, "*", 1);
// 		}
// 		else
// 		{
// 			i = i - j;
// 			write(1, &line[i], 1);
// 			i++;
// 		}
// 	}
// 	write(1, "\n", 1);
// 	return ;
// }

// int	main(int ac, char **av)
// {
// 	// char	*line;
// 	char	buff[BUFFER_SIZE], line1[100000];

// 	if (BUFFER_SIZE < 1 || ac != 2 || !av[1][0])
// 		return (1);
// 	int rd, i, j;
// 	while (1)
// 	{
// 		i = 0;
// 		while (1)
// 		{
// 			rd = read(0, buff, -1);
// 			if (!rd)
// 			{
// 				printline(line1, av[1]);
// 				return (0);
// 			}
// 			else if (rd < 0)
// 				return (perror("Error"), 1);
// 			j = 0;
// 			while (j < rd)
// 			{
// 				if (buff[j] == '\n')
// 					break ;
// 				line1[i] = buff[j];
// 				i++, j++;
// 			}
// 			line1[i] = '\0';
// 			if (buff[j] == '\n')
// 				break ;
// 		}
// 		printline(line1, av[1]);
// 		line1[0] = '\0';
// 	}
// 	return (0);
// }