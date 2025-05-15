/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permut_prepa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:17:44 by mnahli            #+#    #+#             */
/*   Updated: 2025/04/26 09:52:25 by mnahli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	swap(char *a, char *b)
{
	char tmp;
	tmp = *a, *a = *b, *b = tmp;
}

void	sort(char *s)
{
	int i, swapped = 1;
	while (swapped)
	{
		swapped = 0, i = -1;
		while (s[++i+1])
			if (s[i] > s[i+1]) {
				swap(&s[i], &s[i+1]);
				swapped = 1;
			}
	}
}

void	revers(char *s, int start, int end)
{
	while (start < end) {
		swap(&s[start], &s[end]);
		start++, end--;
	}
}

int	permut(char *s, int end)
{
	int i = end-1, j = end;

	while (s[i] >= s[i+1] && i >= 0)
		i--;
	if (i < 0)
		return 0;
	while (s[j] <= s[i] && j > i)
		j--;
	swap(&s[i], &s[j]);
	revers(s, i+1, end);
	return 1;
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return 1;
	if (ac == 2)
		if (!av[1] || !av[1][0])
			return 1;
	int len = 0;
	while (av[1][len])
		len++;
	if (len < 2) {
		puts(av[1]);
		return 0;
	}
	sort(av[1]);
	puts(av[1]);
	while (permut(av[1], len-1))
		puts(av[1]);
	return 0;
}