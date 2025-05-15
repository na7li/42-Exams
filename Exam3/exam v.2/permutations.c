/*
Assignment name : permutations

Expected files : *.c *.h
Allowed functions : puts, malloc, calloc, realloc, free, write
---------------------------------------------------------------

Write a program that will print all the permutations of a string given as argument.

The solutions must be given in alphabetical order.

We will not try your program with strings containing duplicates (eg: 'abccd')

For example this should work:
$> ./permutations a | cat -e
a$
$> ./permutations ab | cat -e
ab$
ba$
$> ./permutations abc | cat -e
abc$
acb$
bac$
bca$
cab$
cba$
*/

#include <stdio.h>
#include <stdlib.h>

void	swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}
void	revers(char *s, int start, int end)
{
	while (start < end)
	{
		swap(&s[start], &s[end]);
		start++, end--;
	}
}

int	permut(char *s, int end)
{
	int i = end - 1, j = end;
	while (s[i] > s[i + 1])
		i--;
	if (i < 0)
		return 0;
	while (s[j] < s[i])
		j--;
	swap(&s[i], &s[j]);
	revers(s, i + 1, end);
	return 1;
}

void	sort(char *s)
{
	int i, sorted = 1;
	if (!s)
		return;
	while (sorted)
	{
		i = 0, sorted = 0;
		while (s[i+1])
		{
			if (s[i] > s[i+1]){
				swap(&s[i], &s[i+1]);
				sorted = 1;}
			i++;
		}
	}
}

int main(int ac, char **av)
{
	if (ac != 2 || !av[1][0])
		return 1;

	int l = 0;
	while (av[1][l])
		l++;
	if (l == 1)
		return puts (av[1]), 0;

	sort(av[1]);
	puts(av[1]);

	int i = 6;
	while ((permut(av[1], l-1)))	// 39al 3la had condition;
		puts(av[1]);

	return 0;
}