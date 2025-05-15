/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mygnl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:54:15 by mnahli            #+#    #+#             */
/*   Updated: 2025/04/25 14:55:08 by mnahli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
9ra mn file des
9ra tal new line => oreje3 f allocated str

open fd
	read char by char
	assign chars to a string to be retuned
	repeat with a while
close fd
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#ifndef BUF_SZ
#define BUF_SZ 4
#endif
#include <stdio.h>

char *gnl(int fd)
{
	int rd, capacity = BUF_SZ, len = 0, i;
	char c, *line, *nwline;

	if (BUF_SZ < 1 || fd < 0)
		return (NULL);
	if ((rd = read(fd, &c, 1)) <= 0)
		return (NULL);
	if (!(line = malloc(capacity + 1)))
		return (NULL);
	while (rd) {
		if (len >= capacity) {
			capacity += BUF_SZ;
			if (!(nwline = malloc(capacity + 1)))
				return (free(line), NULL);
			i = -1;
			while (++i < len)
				nwline[i] = line[i];
			free(line);
			line = nwline;
		}
		line[len++] = c;
		if (c == '\n')
			break ;
		rd = read(fd, &c, 1);
	}
	if (rd < 0)
		return (NULL);
	return (line[len] = '\0', line);
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