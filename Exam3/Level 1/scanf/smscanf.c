#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int c = fgetc(f);
	while(c != EOF && isspace(c))
		c = fgetc(f);
	if(c == EOF)
		return -1;
	ungetc(c,f);
	return 1;
}

int match_char(FILE *f, char c)
{
    int input = fgetc(f);
	if(input == EOF)
		return -1;
	if(input != c)
		return -1;
	ungetc(input,f);
	return 1;
}

int scan_char(FILE *f, va_list ap)
{
    char *caracter = va_arg(ap, char *);
	int c = fgetc(f);
	if(c == EOF)
		return -1;
	*caracter = c;
	return 1;
}

int scan_int(FILE *f, va_list ap)
{
    int number = 0;
	int sign = 1;
	int c = fgetc(f);
	int digit_scanned = 0;

	if(c == '-' || c == '+')
	{
		if(c == '-')
			sign = -1;
		c = fgetc(f);
	}
	while(c != EOF && isdigit(c))
	{
		number = number * 10 + (c - '0');
		c = fgetc(f);
		digit_scanned++;
	}
	if(c != EOF)
		ungetc(c,f);
	if(digit_scanned == 0)
		return 0;
	int *num = va_arg(ap, int *);
	*num = number * sign;
	return 1;
}

int scan_string(FILE *f, va_list ap)
{
    int char_scanned = 0;
	char *str = va_arg(ap,char *);
	int c =  fgetc(f);
	while(c != EOF && !isspace(c))
	{
		str[char_scanned] = c;
		c = fgetc(f);
		char_scanned++;
	}
	str[char_scanned] = '\0';
	if(c != EOF)
		ungetc(c,f); // to expect more input if exist {%s  %d}
	if(char_scanned == 0)
		return 0;
	return 1;
}


int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	if (ferror(f))
		return EOF;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}

int main(void) {
    char *a, b;
    int ret, r, m;

    // Prompt user
    // printf("Enter two integers: ");

    // Read input from stdin
    ret = ft_scanf("%d:%d", &r, &m);

    // Print the results
    printf("'%d' '%d'\n",r, m);
    // printf("ret = %d, a = %d, b = %d, c = %d\n", ret, a, b, c);

    return 0;
}

// int main() {
//     int a = 0, b = -42, c = -42;
//     int ret;
    
//     // Test case 2 (likely input: "0 23")
//     // We expect it to read two values: a=0 and b=23
//     // The current output shows it only reading one value: a=0
//     // The test expects: ret=2, a=0, b=23, c=-42 (c unchanged)
    
//     // Redirect stdin to a string for testing
//     FILE *input = fmemopen(" 0 23", 4, "r");
//     if (!input) {
//         printf("Failed to open memory file\n");
//         return 1;
//     }
    
//     // Temporarily replace stdin
//     FILE *orig_stdin = stdin;
//     stdin = input;
    
//     // Call the scanf function (likely with format "%d %d")
//     ret = ft_scanf("%d %d", &a, &b);
    
//     // Restore stdin
//     stdin = orig_stdin;
//     fclose(input);
    
//     // Print the results
//     printf("2: ret = %d, a = %d, b = %d, c = %d\n", ret, a, b, c);
    
//     return 0;
// }
