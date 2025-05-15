/*
Allowed functions : atoi, printf, malloc, calloc, realloc, free.

your program should display all the subsets of whose sum of elements is n.
Write a program that will take as argument an integer n follow by a set of integers,

In case of a malloc error your program will exit with the code 1.
We will not test invalid test(for example '1 1 2')
hint: the empty set is a subset of anyset.


For example this should work:
$> ./powerset 3 1 0 2 4 5 3 | cat -e
3$
0 3$
1 2$
1 0 2$
$>

$> ./powerset 7 3 8 2| cat -e
$
$>
*/
#include <stdlib.h>
#include <stdio.h>

void	findsubset(int *set, int *subset, int target, int size, int s, int b, int *nwl)
{
	if (s == size)
	{
		int sum = 0, i = -1;
		while (++i < b){
			sum += subset[i];}
		if (sum == target) {
			i = 0, *nwl = 1;
			while (i < b) {
				printf("%d", subset[i++]);
				if (i == b){
					printf("\n");
					return ;
				}
				printf(" ");
			}
		}
		return;
	}
	subset[b] = set[s];
	findsubset(set, subset, target, size, s + 1, b + 1, nwl);
	findsubset(set, subset, target, size, s + 1, b, nwl);
}

int main(int ac, char **av)
{
	if (ac < 3)
		return 0;

	int target = atoi(av[1]);
	int set[ac-2], subset[ac-2], i, nwl = 0;

	i = -1;
	while (++i < ac-2)
		set[i] = atoi(av[i + 2]);

	findsubset(set, subset, target, ac-2, 0, 0, &nwl);
	if (!nwl)
		printf("\n");
	return (0);
}
