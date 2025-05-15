/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnahli <mnahli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:05:15 by mnahli            #+#    #+#             */
/*   Updated: 2025/04/26 12:08:33 by mnahli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	findsubset(int *set, int *subset, int target, int size, int i, int j, char *nwl)
{
	if (i == size)
	{
		int k = -1, sum = 0;
		while (++k < j)
			sum += subset[k];
		if (sum == target)
		{
			k = -1;
			while (++k < j)
			{
				printf("%d", subset[k]);
				if (k == j - 1) {
					printf("\n");
					break ;
				}
				printf(" ");
			}
			*nwl = 'Y';
		}
		return ;
	}
	subset[j] = set[i];
	findsubset(set, subset, target, size, i+1, j+1, nwl);
	findsubset(set, subset, target, size, i+1, j, nwl);
}

int main(int ac, char **av)
{
	if (ac < 3)
		return 1;
	char nwl = 'N';
	int target = atoi(av[1]);
	int size = ac - 2;
	int *set = malloc(sizeof(int) * size);
	int *subset = malloc(sizeof(int) * size);
	if (!set || !subset)
		return (free(set), free(subset), 1);
	int i = -1;
	while (++i < size)
		set[i] = atoi(av[i + 2]);
	findsubset(set, subset, target, size, 0, 0, &nwl);
	if (nwl == 'N')
		printf("\n");
	return (free(set), free(subset), 0);
}