/*
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


void	swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort(char *s, int len)
{
	int i, swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (s[i+1])
		{
			if (s[i] > s[i+1]) {
				swap(&s[i], &s[i+1]);
				 swapped = 1;
				 break;
			}
			i++;
		}
	}
}

void	revers(char *s, int start, int end)
{
	while (start < end) {
		swap(&s[start], &s[end]);
		start++;
		end--;
	}
}

int	permut(char *s, int end)
{
	// find i
	int i = end - 1, j = end;
	while (s[i] > s[i+1] && i >= 0)
		i--;
	if (i < 0)
		return 0;
	// find j
	while (s[j] < s[i] && j >= i)
		j--;
	if (j <= i)
		return 0;

	// swap
	swap(&s[i], &s[j]);
	// reverse
	revers(s, i+1, end);
	return 1;
}

int main(int ac, char **av)
{
	if (ac != 2)
		return 1;
	if (!av[1] || !av[1][0])
		return 1;

	int len = 0;
	while (av[1][len])
		len++;
	if (len == 1) {
		puts(av[1]);
		return 0;	}

	// sort -> using swap
	sort(av[1], len);
	// print sorted one -> puts
	puts(av[1]);
	// permut
	while (permut(av[1], len-1))
		puts(av[1]);

	return 0;
}