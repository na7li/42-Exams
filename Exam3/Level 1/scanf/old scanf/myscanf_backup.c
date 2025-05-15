#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>

void skip_input_space()
{
    // Input your code here
	int ch = fgetc(stdin);
	while (isspace(ch))
		ch = fgetc(stdin);
	ungetc(ch, stdin);
}

int scan_int(va_list ap)
{
    // Input your code here
	int	sign=1, result=0;

	skip_input_space();
	int ch = fgetc(stdin);
	if (ch == '-' || ch == '+')
	{
		if (ch == '-')
			sign = -1;
		ch = fgetc(stdin);
	}
	if (!isdigit(ch))
		return (ungetc(ch, stdin), 0);
	while (isdigit(ch))
	{
		result = result * 10 + (ch - '0');
		ch = fgetc(stdin);
	}
	if (result == 0 && ch != '0')
		return (0);
	result *= sign;
	int *ptr = va_arg(ap, int*);
	return (*ptr = result, 1);

}

int scan_string(va_list ap, int flag)
{
    // Input your code here
	skip_input_space();
	int ch = fgetc(stdin);
	if (ch == EOF)
		return (0);
	char *ptr = va_arg(ap, char*);
	*ptr = (char)ch;
	if (flag == 2)
		return (1);
	int count = 0;
	while (ch != EOF && !isspace(ch))
	{
		ptr++;
		ch = fgetc(stdin);
		*ptr = (char)ch;
		if (ch == EOF)
			break ;
		count++;
	}
	*ptr = '\0';
	return (count);
}

int	ft_scanf(const char *format, ...)
{
	va_list	ap;
	int i = 0,j = 0, ch;

	va_start(ap, format);
	while(format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == 'c'){
				if (scan_string(ap, 2))
					j++;}
			if (format[i] == 's'){
				if (scan_string(ap, 0))
					j++;}
			if (format[i] == 'd'){
				if(scan_int(ap))
					j++;}
		}
		else
			i++;
	}
	return (j);
}

int main(void)
{
	char c, *str;
	char *str_g;
	int ptr;


	int i = scanf("%s ", str);
	printf("print:  %s\nreturn: %d\n\n", str, i);
	// int i = ft_scanf("%c", &c);
	// printf("print:  %c \nreturn: %d\n\n", c, i);
	// int i = scanf(" %d ", &ptr);		// difference in number only
	// printf("print:  %d\nreturn: %d\n\n", ptr, i);

	// int i = ft_scanf(" %s %c ", str, &c);		// difference
	// printf("print:  %s\nchar:   %c\nreturn: %d\n\n", str, c, i);

	// int i = scanf(" %s %c %d ", str, &c, &ptr);
	// printf("Name: %s \n gender: %c \n age:%d\nreturn: %d\n\n", str, c,ptr,  i);

	return (0);
}


// #include <stdarg.h>
// #include <unistd.h>
// #include <stdio.h>
// #include <ctype.h>

// static void skip_space(void)
// {
// 	int ch;
// 	while ((ch = fgetc(stdin)) != EOF && isspace(ch))
// 		;
// 	if (ch != EOF)
// 		ungetc(ch, stdin);
// }

// static int scan_int(va_list ap)
// {
// 	int sign = 1, result = 0, ch;

// 	skip_space();
// 	ch = fgetc(stdin);
// 	if (ch == '-' || ch == '+')
// 	{
// 		if (ch == '-')
// 			sign = -1;
// 		ch = fgetc(stdin);
// 	}
// 	if (!isdigit(ch))
// 		return (ungetc(ch, stdin), 0);
// 	while (isdigit(ch))
// 	{
// 		result = result * 10 + (ch - '0');
// 		ch = fgetc(stdin);
// 	}
// 	if (ch != EOF)
// 		ungetc(ch, stdin);
// 	return (*va_arg(ap, int *) = result * sign, 1);
// }

// static int scan_string(va_list ap, int is_char)
// {
// 	char *ptr = va_arg(ap, char *);
// 	int ch;

// 	skip_space();
// 	ch = fgetc(stdin);
// 	if (ch == EOF)
// 		return (0);
// 	*ptr++ = (char)ch;
// 	if (is_char)
// 		return (1);
// 	while ((ch = fgetc(stdin)) != EOF && !isspace(ch))
// 		*ptr++ = (char)ch;
// 	*ptr = '\0';
// 	return (1);
// }

// int ft_scanf(const char *format, ...)
// {
// 	va_list ap;
// 	int i = 0, success = 0;

// 	va_start(ap, format);
// 	while (format[i])
// 	{
// 		if (format[i] == '%')
// 		{
// 			if (format[++i] == 'c' && scan_string(ap, 1))
// 				success++;
// 			else if (format[i] == 'd' && scan_int(ap))
// 				success++;
// 			else if (format[i] == 's' && scan_string(ap, 0))
// 				success++;
// 		}
// 		i++;
// 	}
// 	va_end(ap);
// 	return (success);
// }

