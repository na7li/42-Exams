/*
Allowed functions : atoi, fprintf, write

-------------------------------------------------------------------------

Write a program that will print all the solutions to the n queens problem
for a n given as argument.
We will not test with negative values.
The order of the solutions is not important.

You will display the solutions under the following format :
<p1> <p2> <p3> ... \n
where pn are the line index of the queen in each colum starting from 0.

For example this should work :
$> ./n_queens 2 | cat -e

$> ./n_queens 4 | cat -e
1 3 0 2$
2 0 3 1$

$> ./n_queens 7 | cat -e
0 2 4 6 1 3 5$
0 3 6 2 5 1 4$
*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
void	printres(int *queen_sz, int size)
{
	int i = 0;

	while (i < size)
	{
		fprintf(stdout, "%d", queen_sz[i]);
		if (i < size - 1)
			fprintf(stdout, " ");
		else
			fprintf(stdout, "\n");
		i++;
	}
	// write(1, "\n", 1);
}

int		issafe(int *queen_sz, int row, int col)
{
	int prevcol = 0;
	while (prevcol < col)
	{
		if (row == queen_sz[prevcol] ||
			row - queen_sz[prevcol] == col - prevcol ||
			queen_sz[prevcol] - row == col - prevcol)
			return 0;
		prevcol++;
	}
		return 1;
		// printf("CHNAHOWA\n");
}

void	solve(int *queen_sz, int col, int size)
{
	int row = 0;
	if (col == size) {
		printres(queen_sz, size);
		return ;}
	while (row < size)
	{
		if (issafe(queen_sz, row, col)) {
			queen_sz[col] = row;
			solve(queen_sz, col+1, size);
		}
		row++;
	}
}

int main(int ac, char **av)
{
	if (ac != 2 || !av[1] || !av[1][0])
		return 0;
	int i = atoi(av[1]);
	if (i < 1)
		return 0;
	int queen_sz[i];

	solve(queen_sz, 0, i);

	return 0;
}