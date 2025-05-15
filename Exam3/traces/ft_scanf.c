#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
// '    EOF'
// '    c'
int match_space(FILE *f)
{
	int c = fgetc(f);
	while (isspace(c))
		c = fgetc(f);
	if (c == EOF)
		return -1;
	ungetc(c, f);
	return 1;
}

int match_char(FILE *f, char c)
{
    char b  = fgetc(f);
	if(b == EOF)
		return -1;
	if (b != c)
		return ungetc(b,f), -1;
	return 1;
}
// 'all except EOF'
int scan_char(FILE *f, va_list ap)
{
    char c = fgetc(f);
	if (c == EOF)
		return -1;
	char *ptr = va_arg(ap, char*);
	*ptr = c;
	return 1;
}
// cases
// '-123'
// '-123 kjh'
// '123'
// '123 '
// '123kj'
// '-sfj'
// 'jhg'
// 'EOF'
int scan_int(FILE *f, va_list ap)
{
	int nb = 0, sign = 1, scanned = 0, *res;
	int c = fgetc(f);
	if (!isdigit(c) && c != '-' && c != '+')
		return -1;
	if (c == '-' || c == '+')
	{
		if (c == '-')
			sign = -1;
		c = fgetc(f);
	}
	while (isdigit(c))
	{
		nb = (nb * 10) + (c - '0');
		c = fgetc(f);
		scanned = 1;
	}
	if (c != EOF)
		ungetc(c, f);
	if (!scanned)
		return 0;
	res = va_arg(ap, int*);
	*res = nb * sign;
	return 1;
}
// 'all except 'space' and 'EOF' '
// 'EOF'
// '   EOF'
// 'abc'
// 'abc hgf'
// 'fjkh~@![p@lkdsj]GJJF564'
int scan_string(FILE *f, va_list ap)
{
    int c = fgetc(f);
	char *ptr = va_arg(ap, char*);
	int scanned = 0;
	while (!isspace(c) && c != EOF)
	{
		scanned = 1;
		*ptr++ = c;
		c = fgetc(f);
	}
	if (c != EOF)
		ungetc(c, f);
	if (!scanned)
		return -1;
	*ptr = '\0';
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

//// msa7 intain
// cases
// 'all except 'space' and 'EOF' '
// 'EOF'
// '   EOF'
// 'abc'
// 'abc hgf'
// 'fjkh~@![p@lkdsj]GJJF564'
int main(void)
{
    char a;
    int b;

    // Simulate this input: "a 12"
    // The user probably ran your program with input: a<space>12<Enter>
    // Or redirected from a file

    int ret = scanf("%c/%d", &a, &b);

    printf("ret = %d, a = %c, b = %d$\n", ret, a, b);
    return 0;
}

// int main()
// {
// 	// char s[50], c;
// 	int ret;
// 	char a[50];
// 	ret = scanf(" %s", a);
// 	printf("ret = %d, a = %s\n", ret, a);
// 	// char a;
// 	// int b;
// 	// ret = ft_scanf("%c %d", &a, &b);
// 	// printf("ret = %d, a = %c, b = %d\n", ret, a, b);
// 	return 1;
// }