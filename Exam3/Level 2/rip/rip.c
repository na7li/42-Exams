/*
Allowed functions: puts, write
--------------------------------------------------------------------------------
Write a program that will take as argument a string containing only parenthesis.
If parenthesis are unbalanced (for example "())") your program shall remove the
minimum number of parenthesis for the expression to be balanced.
By removing we mean replacing by spaces.
You will print all the solutions (can be more than one).
The order of the solutions is not important.
For example this should work:
(For readability reasons the '_' means space and the spaces are for readability only.)
$> ./rip '( ( )' | cat -e
_ ( ) $
( _ ) $
$> ./rip '( ( ( ) ( ) ( ) ) ( ) )' | cat -e
( ( ( ) ( ) ( ) ) ( ) ) $
$> ./rip '( ) ( ) ) ( )' | cat -e
( ) ( ) _ ( ) $
( ) ( _ ) ( ) $
( _ ( ) ) ( ) $
$> ./rip '( ( ) ( ( ) (' | cat -e
( ( ) _ _ ) _ $
( _ ) ( _ ) _ $
( _ ) _ ( ) _ $
_ ( ) ( _ ) _ $
_ ( ) _ ( ) _ $
*/

// rm cal
// solve

#include <stdio.h>
#include <unistd.h>

int		rmclcl(char *s)
{
	if (!s)
		return -1;
	int open = 0, i = 0;

	while (s[i])
	{
		if (s[i] == '(')
			open++;
		else if (s[i] == ')')
			open--;
		i++;
	}
	if (open < 0)
		return (open * -1);
	return (open);
}

void	solve(char *str, char *buff, int size, int rm, int open, int s, int b)
{
	if (b == size)
	{
		if (!open && !rm)
			puts(buff);
		return ;
	}
	if (rm > 0)
	{
		buff[b] = '_';
		solve(str, buff, size, rm-1, open, s+1, b+1);
	}
	if (str[s] == '(') {
		buff[b] = '(';
		solve(str, buff, size, rm, open+1, s+1, b+1);
	}
	else if (str[s] == ')') {
		if (open > 0) {
			buff[b] = ')';
			solve(str, buff, size, rm, open-1, s+1, b+1);
		}
	}
	else {
		buff[b] = str[s];
		solve(str, buff, size, rm, open, s+1, b+1);
	}
}

int main(int ac, char **av)
{

	if (ac != 2 || !av[1] || !av[1][0])
		return 0;

	int i = 0;
	while (av[1][i])
		i++;

	char buff[i];

	int rm = rmclcl(av[1]);
	solve(av[1], buff, i, rm, 0, 0, 0);
	return 0;
}
