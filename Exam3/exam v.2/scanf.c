#include <ctype.h>
#include <stdio.h>
#include <stdarg.h>

// Allowed functions: fgetc, ungetc, ferror, feof, isspace, isdigit, stdin, 
// va_start, va_arg, va_copy, va_end

int match_space(FILE *f)
{
	char s = fgetc(f);
	while (isspace(s))
		s = fgetc(f);
	if (s == EOF)
		return -1;
	ungetc(s, f);
	return 1;
}

int match_char(FILE *f, char c)
{
	char b = fgetc(f);
	if (b != c)
		return -1;
	return 1;
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
/*
'123' / '-123'
'123 '
'123sd'
'ksjfh' / '-ksjfh'
''
*/
int scan_int(FILE *f, va_list ap)
{
	int c = fgetc(f), sign = 1, nbr = 0, *res;
	if (!isdigit(c) && c != '-' && c != '+')
		return -1;
	if (c == '+' || c == '-') {
		if (c == '-')
			sign = -1;
		c = fgetc(f);
	}
	if (!isdigit(c))
		return -1;
	while (isdigit(c))
	{
		nbr = (nbr * 10) + (c - '0');
		c = fgetc(f);
	}
	res = va_arg(ap, int *);
	*res = nbr * sign;
	if (c != EOF)
		ungetc(c, f);
	return 1;
}
/*
'stops on white spaces & EOF'
*/
// 'gEOF'
int scan_string(FILE *f, va_list ap)
{
	char c = fgetc(f), *ptr = va_arg(ap, char *);
	if (c == EOF)
		return -1;
	while (c != EOF && !isspace(c))
	{
		*ptr++ = c;
		c = fgetc(f);
	}
	*ptr = '\0';
	if (c != EOF)
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

/*************************/
// #include <stdio.h>
// int main()
// {
// 	char *s;
// 	char c;
// 	int d;
// 	// ft_scanf(" %s", s);
// 	// printf("s: %s", s);
// 	ft_scanf(" %c %d %s", &c, &d, s);
// 	printf("c: '%c'\nd: '%d'\ns: '%s'", c, d, s);
// 	return 0;
// }


#include <stdio.h>
#include <string.h>

int main()
{
	char c;
	int d;
	char s[100]; // make sure to allocate enough space
	int ret = ft_scanf("%c%d%s", &c, &d, s);
	printf("ret=%d\nc:%c - d:%d - s:%s", ret, c, d, s);
	return 0;
}


