#include <stdio.h>

void	swap(char *a, char *b)
{
	char tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
	return ;
}

void sort(char *str)
{
	int	i, swapped = 1;
	while (swapped)
	{
		i = -1, swapped = 0;
		while (str[++i + 1])
			if (str[i] > str[i + 1]) {
				swap(&str[i], &str[i + 1]);
				swapped = 1;}
	}
	return ;
}

void	revers(char *str, int start, int end)
{
	while (start < end)
	{
		swap(&str[start], &str[end]);
		start++;
		end--;
	}
}

int	permut(char *str, int end)
{
	if (!str)
		return (0);
	int i = end - 1, j = end;

	while (str[i] >= str[i + 1])
		i--;
	if (i < 0)
		return (0);
	while (str[j] <= str[i])
		j--;
	swap(&str[j], &str[i]);
	revers(str, i + 1, end);
	return (1);
}

int main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	sort(av[1]);
	puts(av[1]);
	int len = 0;
	while(av[1][len])
		len++;
	while ((permut(av[1], len - 1)) != 0)
		puts(av[1]);
	return (0);
}


/****************/

// void	swap(char *a, char *b)
// {
// 	char tmp = *a;
// 	*a = *b;
// 	*b = tmp;
// }

// void	reverse(char *str, int start, int end)
// {
// 	while (start < end)
// 	{
// 		swap(&str[start], &str[end]);
// 		start++;
// 		end--;
// 	}
// }

// int	next_permutation(char *str, int len)
// {
// 	int i = len - 2;

// 	// Step 1: Find the first character from the end which is smaller than the next
// 	while (i >= 0 && str[i] >= str[i + 1])
// 		i--;
// 	if (i < 0)
// 		return (0); // All permutations done

// 	// Step 2: Find the next larger character to swap with
// 	int j = len - 1;
// 	while (str[j] <= str[i])
// 		j--;

// 	swap(&str[i], &str[j]);

// 	// Step 3: Reverse the suffix
// 	reverse(str, i + 1, len - 1);
// 	return (1);
// }

// void	sort_string(char *str)
// {
// 	int i, swapped;
// 	swapped = 1;
// 	while (swapped)
// 	{
// 		swapped = 0;
// 		i = 0;
// 		while (str[i + 1])
// 		{
// 			if (str[i] > str[i + 1])
// 			{
// 				swap(&str[i], &str[i + 1]);
// 				swapped = 1;
// 			}
// 			i++;
// 		}
// 	}
// }

// int	main(int argc, char **argv)
// {
// 	int len = 0;

// 	if (argc != 2)
// 		return (1);

// 	while (argv[1][len])
// 		len++;

// 	sort_string(argv[1]);       // Step 0: Sort to start with smallest permutation
// 	puts(argv[1]);        // Print the first permutation

// 	while (next_permutation(argv[1], len))
// 		puts(argv[1]);

// 	return (0);
// }
