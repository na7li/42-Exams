#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// problem: find all possible ways to place N queens on the board so that no two queens share the same row, column or dioognal .
// solution: placing queens one by one + check if new queen placement is safe + record and p[rint each valid arrangement .
void    print_solution(int *board, int n)
{
    int i;
	
	i = 0;
    while (i < n)
    {
        fprintf(stdout, "%d", board[i]);
        if (i < n - 1)
            fprintf(stdout, " ");
        else
            fprintf(stdout, "\n");
        i++;
    }
}

// check if placing a queen at (col, row) is safe .
// no two queens in the same row or column .
int is_safe(int *board, int col, int row)
{
	int i;
	
	i = 0;
	while (i < col)
	{
		if (board[i] == row || 
			board[i] - row == col - i || 
			row - board[i] == col - i)
			return (0);
		i++;
	}
	return (1);
}

// if all queens are placed print the board .
// for each row in the current column + if the position is safe + place the queen + recurse to the next column .
void solve_nqueen(int *board, int col, int n)
{
	int row;

	row = 0;
	if (col == n)
	{
		print_solution(board,n);
		return ;
	}
	while (row < n)
	{
		if (is_safe(board,col,row))
		{
			board[col] = row;
			solve_nqueen(board,col + 1,n);
		}
		row++;
	}
	return ;
}

// expect one argument .
// convert it to integer .
// allocates memory for the board .
// call solve_nqueen from column 0 .
// free the board and exit .
int main(int argc, char **argv)
{
	int *board;
	int n;

	if(argc != 2)
		return 1;
	n = atoi(argv[1]);
	if(n <= 0)
		return (1);
	if (!(board = malloc(sizeof(int) * n)))
		return (1);
	solve_nqueen(board, 0, n);
	free(board);
	return (0);
}
