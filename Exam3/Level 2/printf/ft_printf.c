#include <stdarg.h>
#include <unistd.h>

void	ft_putstr(char *str, int *len)
{
	if (!str)
		str = "(null)";
	while (*str)
		*len += write(1, str++, 1);
}

void	ft_putnbr(long long int num, int *len, int base)
{
	if (num < 0)
	{
		num *= -1;
		*len += write(1, "-", 1);
	}
	if (num >= base)	// i did (num > 9) => wrong
		ft_putnbr((num/base), len, base);
	*len += write(1, &"012345689abcdef"[num % base], 1);
}

int ft_printf(const char * format, ...)
{
	int	len = 0;
	va_list	ap;

	va_start(ap, format);
	while (*format)
	{
		if (*format == '%' && *(format+1)) // I've to check *(format+1)
		{
			format++;
			if (*format == 's')
				ft_putstr(va_arg(ap, char*), &len);
			if (*format == 'd')
				ft_putnbr((long long int)va_arg(ap, int), &len, 10);
			if (*format == 'x')
				ft_putnbr((long long int)va_arg(ap, int), &len, 16);
		}
		else
			len += write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (len);
}


#include <stdio.h>
int main(void)
{
	ft_printf("\ntotal char: %d", ft_printf("Hello %s we'll have %dK USD per day in the %x Bank;%%", NULL, 2025, 123456));
	ft_printf("\n\norigigal:\n");
	   printf("\ntotal char: %d\n", ft_printf("Hello %s we'll have %dK USD per day in the %x Bank;%%", NULL, 2025, 123456));
	return (0);
}