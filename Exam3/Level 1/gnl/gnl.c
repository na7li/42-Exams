/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:04:41 by mnahli            #+#    #+#             */
/*   Updated: 2025/04/22 09:46:04 by mnahli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define BUF_SZ 4
#include <stdio.h>

/*	Read char by char -> store char in a str -> return the str	*/

char*	gnl(int fd)
{
	char	c, *line, *nw_line;
	int		rd, lenth =0, i, capacity = BUF_SZ;

	if (BUF_SZ < 1 || fd < 0)
		return (NULL);
	if (!(line = malloc(capacity + 1)))
		return (NULL);
	while ((rd = read(fd, &c, 1)) > 0)
	{
		if (lenth >= capacity)
		{
			capacity += BUF_SZ;
			if(!(nw_line = malloc(capacity + 1)))
				return (free(line), NULL);
			i = -1;
			while (++i < lenth)
				nw_line[i] = line[i];
			free(line);
			line = nw_line;
		}
		line[lenth++] = c;
		if (c == '\n')
			break;
	}
	if (rd < 0 || (rd == 0 && lenth == 0))
		return (free(line), NULL);
	return (line[lenth] = '\0', line);
}

int	main(int ac, char	**av)
{
	int		fd, i = -1;
	char	*line;
	(void)ac;
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (write(1, "Error\n", 6), 1);

	line = gnl(fd);
	while (line)
	{
		while (line[++i])
			write(1, &line[i], 1);
		i = -1;
		free(line);
		line = gnl(fd);
	}
	close (fd);
	return (0);
}
