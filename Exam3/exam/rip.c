#include <stdio.h>

// '(()'
/*
1. rm clcl
2. print the combination that open ==0 and rm = 0;
*/

int	par_clcl(char *av)
{
	int i = 0, open = 0;

	while (av[i])
	{
		if (av[i] == '(')
			open++;
		else if (av[i] == ')')
			open--;
		i++;
	}
	if (open < 0)
		return (open * -1);
	return open;
}

void	solve(char *av, char *buff, int size, int rm, int open, int s, int b)
{
	if (b == size)
	{
		if (open == 0 && rm == 0) {
			buff[b] = '\0';
			puts(buff);
		}
		return ;
	}
	if (rm > 0) {
		buff[b] = ' ';
		solve(av, buff, size, rm-1, open, s+1, b+1);
	}
	if (av[s] == '(') {
		buff[b] = '(';
		solve(av, buff, size, rm, open+1, s+1, b+1);
	}
	else if (av[s] == ')') {
		if (open > 0) {
			buff[b] = ')';
			solve(av, buff, size, rm, open-1, s+1, b+1);
		}
	}
	else {
		buff[b] = av[s];
		solve(av, buff, size, rm, open, s+1, b+1);
	}
}

int main(int ac, char **av)
{
	if (ac != 2)
		return 1;
	int len = 0;
	while (av[1][len])
		len++;
	int rm = par_clcl(av[1]);
	char buff[len + 1];
	solve(av[1], buff, len, rm, 0, 0, 0);
	return 0;
}
