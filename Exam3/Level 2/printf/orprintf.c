#include <unistd.h>
#include <stdarg.h>

void	ft_putstr(char *str, int *len)
{
	if (!str)
		str="(null)";
	while (*str)
		*len += write(1, str++, 1);
}

void ft_int(long long int nb, int *len, int base)
{
	if (nb < 0)
	{
		nb *= -1;
		*len += write(1, "-", 1);
	}
	if (nb >= base)
		ft_int((nb / base), len, base);
	*len += write(1, &"0123456789abcdef"[nb % base], 1);
}

int	ft_printf(const char *format, ...)
{
	int	len = 0;
	va_list	args;

	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(format+1))
		{
			format++;
			if (*format == 's')
				ft_putstr(va_arg(args, char*), &len);
			if (*format == 'd')
				ft_int((long long int)va_arg(args, int), &len, 10);
			if (*format == 'x')
				ft_int((long long int)va_arg(args, int), &len, 16);
		}
		else
			len += write(1, format, 1);
		format++;
	}
	va_end(args);
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