#include <stdio.h>

void solve(char *str, char *buff, int rm, int open, int s, int b)
{
	if (!str[s]) {
		if (open == 0 && rm == 0) {
			buff[b] = '\0';
			puts(buff);
		}
		return;
	}
	if (rm > 0) {
		buff[b] = '_';
		solve(str, buff, rm - 1, open, s+1, b+1);
	}
	if (str[s] == '(') {
		buff[b] = '(';
		solve(str, buff, rm, open + 1, s+1, b+1);
	}
	else if (str[s] == ')') {
		if (open > 0) {
			buff[b] = ')';
			solve(str, buff, rm, open - 1, s+1, b+1);}
	}
	else {
		buff[b] = str[s];
		solve(str, buff, rm, open, s+1, b+1);
	}
}

int rmclcl(char *str)
{
	int i = -1, open = 0, close = 0;
	while (str[++i]) {
		if (str[i] == '(')
			open++;
		else if (str[i] == ')')
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
	int rm = rmclcl(av[1]);
	solve(av[1], buff, rm, 0, 0, 0);
	return 0;
}

/**     START CODE WORK     **/

// void	solve(char *str, char *buff, int open, int rm, int b, int s)
// {
// 	if(!str[s]) {
// 		if (open == 0 && rm == 0) {
// 			puts(buff);
// 		}
// 		return;
// 	}
// 	if(rm > 0) {
// 		buff[b] = '_';
// 		solve(str, buff, open, rm - 1, b + 1, s + 1);
// 	}
// 	if(str[s] == '(') {
// 		buff[b] = '(';
// 		solve(str, buff, open + 1, rm, b + 1, s + 1);
// 	}
// 	else if(str[s] == ')') {
// 		if (open > 0){
// 		buff[b] = ')';
// 		solve(str, buff, open - 1, rm, b + 1, s + 1);}
// 	}
// 	else {
// 		buff[b] = str[s];
// 		solve(str, buff, open, rm, b + 1, s + 1);
// 	}
// }

// int	to_rm(char *str)
// {
// 	int i = 0, open = 0, close = 0;
// 	while (str[i]) {
// 		if (str[i] == '(')
// 			open++;
// 		else if (str[i] == ')')
// 			close++;
// 		i++;
// 	}
// 	if ((open - close) < 0)
// 		return ((open - close) * -1);
// 	return (open - close);
// }

// int main(int ac, char **av)
// {
// 	if (ac != 2)
// 		return (1);
// 	int len = 0;
// 	while (av[1][len])
// 		len++;
// 	char buff[len + 1];
// 	int rm = to_rm(av[1]);
// 	solve(av[1], buff, 0, rm, 0, 0);
// 	return (0);
// }