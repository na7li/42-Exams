#include <ctype.h>
#include <stdio.h>
#include <stdarg.h>

//Allowed functions: fgetc, ungetc, ferror, feof, isspace, isdigit, stdin, 
//va_start, va_arg, va_copy, va_end

int match_space(FILE *f)
{
	char c = fgetc(f);
	while (isspace(c))
		c = fgetc(f);
	if (c == EOF)
		return -1;
	else
		ungetc(c, f);
	return 1;
}

int match_char(FILE *f, char c)
{
    char b = fgetc(f);
	if (b == c)
		return 1;
	return -1;
}

int scan_char(FILE *f, va_list ap)
{
    char c = fgetc(f);
	if (c == EOF)
		return -1;
	char *b = va_arg(ap, char *);
	*b = c;
	return 1;
}

int scan_int(FILE *f, va_list ap)
{
	int nb = 0, r = 0, valid = 0, sign = 1;
	nb = fgetc(f);
	if (nb == '-' || nb == '+')
	{
		if (nb == '-')
			sign = -1;
		nb = fgetc(f);
	}
	while (isdigit(nb))
	{
		valid = 1;
		r = r * 10 + (nb - '0');
		nb = fgetc(f);
	}
	if (!valid)
		return -1;
	if (nb != EOF)
		ungetc(nb, f);
	int *num = va_arg(ap, int *);
	*num = sign * r;
	return 1;
}

    /* stop EOF or ' ' */
	// 'gEOF'
int scan_string(FILE *f, va_list ap)
{
	char c = fgetc(f), *s = va_arg(ap, char *);
	int valid = 0;
	while (!isspace(c) && c != EOF)
	{
		valid = 1;
		*s++ = c;
		c = fgetc(f);
	}
	*s = '\0';
	if (!valid)
		return -1;
	if (isspace(c))
		ungetc(c, f);
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
	/**/
	va_list ap;
	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	/**/
	return ret;
}

int main(void) {
    char *s, *a, *c, e;
	int d;

	ft_scanf("%s %s %d %s %c", s, a, &d, c, &e);
	printf("%s, %s, %d, %s, %c", s, a, d, c, e);
    return 0;
}

// int main(void) {
//     char a[100], b[100], c;
//     int ret, r, f, d;

// 	scanf("%d", &d);
// 	printf("'%d'", d);
//     // ret = ft_scanf(" %s %s", a, b);
//     // printf("'%s' '%s'\n", a, b);
// 	// printf("ret = %d\n", ret);
//     // Prompt user
//     // printf("Enter two integers: ");

//     // Read input from stdin

//     // Print the results
//     // printf("ret = %d, a = %d, b = %d, c = %d\n", ret, a, b, c);

//     return 0;
// }
