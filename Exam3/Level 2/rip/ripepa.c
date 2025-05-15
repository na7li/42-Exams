#include <stdio.h>

void	rip(char *s, char *buff, int rm, int open, int i, int j)
{
	if (!s[i]) {
		if (rm == 0 && open == 0) {
			buff[j] = '\0';
			puts(buff);}
		return ;
	}
	if (rm > 0) {
		buff[j] = '_';
		rip(s, buff, rm-1, open, i+1, j+1);
	}
	if (s[i] == '(') {
		buff[j] = '(';
		rip(s, buff, rm, open+1, i+1, j+1);
	}
	else if (s[i] == ')') {
		if (open > 0) {
			buff[j] = ')';
			rip(s, buff, rm, open-1, i+1, j+1);
		}
	}
	else {
		buff[j] = s[i];
		rip(s, buff, rm, open, i+1, j+1);
	}
}

int	calculateip(char *s)
{
	int i = -1, open = 0, close = 0;

	while (s[++i]) {
		if (s[i] == '(')
			open++;
		else if (s[i] == ')')
			close++;
	}
	if ((open - close) < 0)
		return ((open - close) * -1);
	return (open - close);
}

int main(int ac, char **av)
{
	if (ac != 2)
		return 1;

	int len = 0;
	while (av[1][len])
		len++;
	char buff[len + 1];
	int rm = calculateip(av[1]);
	rip(av[1], buff, rm, 0, 0, 0);
	return 0;
}