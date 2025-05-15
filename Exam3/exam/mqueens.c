#include <stdio.h>
#include <stdlib.h>

void	printpos(int *queen_rows, int board_sz)
{
	int i = 0;
	while (i < board_sz)
	{
		fprintf(stdout, "%d", queen_rows[i]);
		if (i < board_sz - 1)
			fprintf(stdout, " ");
		else
			fprintf(stdout, "\n");
		i++;
	}
}

int		issafe(int *queen_rows, int col, int row)
{
	int prev_col = 0;
	while (prev_col < col)
	{
		if (queen_rows[prev_col] == row ||
			row - queen_rows[prev_col] == col - prev_col  ||
			queen_rows[prev_col] - row == col - prev_col)
				return 0;
		prev_col++;
	}
	return 1;
}

void	solve(int *queen_rows, int col, int board_sz)
{
	int row = 0;
	// print
	if (col == board_sz)
	{
		printpos(queen_rows, board_sz);
		return ;
	}
	// solve
	while (row < board_sz)
	{
		if (issafe(queen_rows, col, row)) {
			queen_rows[col] = row;
			solve(queen_rows, col+1, board_sz);
		}
		row++;
	}
	return ;
}

int main(int ac, char **av)
{
	if (ac != 2 || !av[1] || !av[1][0])
		return 1;

	int board_sz = atoi(av[1]);
	if (board_sz < 1)
		return 0;

	int *queen_rows = malloc(sizeof(int) * board_sz);
	if (!queen_rows)
		return 1;

	solve(queen_rows, 0, board_sz);
	free(queen_rows);
	return 1;
}