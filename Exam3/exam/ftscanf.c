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
	ungetc(c, f);
	return 1;
}

int match_char(FILE *f, char c)
{
	char a = fgetc(f);
	if (a == c)
		return 1;
	return -1;
}

int scan_char(FILE *f, va_list ap)
{
	char c = fgetc(f);
	if (c == EOF)
		return -1;
	char *p = va_arg(ap, char *);
	*p = c;
	return 1;
}

/*
// '  abc1337'
// ''

'1337'
'1337abc'
'1337  '
'fghgh'
*/
int scan_int(FILE *f, va_list ap)
{
	int c = fgetc(f), scanned = 0;
	if (!isdigit(c) && c != '-' && c != '+')
		return -1;
	int nb = 0, sign = 1, *num;
	if (c == '-' || c == '+')
	{
		if (c == '-')
			sign = -1;
		c = fgetc(f);
	}
	while (isdigit(c))
	{
		nb = nb * 10 + (c - '0');
		c = fgetc(f);
		scanned++;
	}
	if (!scanned)	// added scanned int to protect this case ' -df'
		return -1;
	num = va_arg(ap, int*);
	*num = nb * sign;
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
	char c = fgetc(f);
	int scanned = 0;
	if (c == EOF)
		return -1;
	char *p = va_arg(ap, char *);
	while (!isspace(c) && c != EOF)
	{
		*p++ = c;
		c = fgetc(f);
		scanned = 1;
	}
	if (!scanned)	// added scanned to protect 'spaces+EOF' case '   EOF'
		return 0;
	*p = '\0';
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
	int d;

	ft_scanf("%d", &d);
	printf("%d", d);
    return 0;
}
