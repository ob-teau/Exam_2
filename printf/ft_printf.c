/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alice <acoinus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 09:05:36 by alice             #+#    #+#             */
/*   Updated: 2022/02/24 11:07:00 by alice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(t_info *f, char c)
{
	if (write(1, &c, 1))
		f->ret++;
	return ;
}

void	print_s(t_info *f, char *s)
{
	int	i = -1;

	while (s[++i])
		ft_putchar(&*f, s[i]);
}

void	print_d(t_info *f, int	n)
{
	if (n < 0)
	{
		ft_putchar(*&f, '-');
		n *= - 1;
	}
	if (n < 9)
		ft_putchar(*&f, n + 48);
	if (n > 9)
	{
		print_d(*&f, n / 10);
		ft_putchar(*&f, n % 10 + 48);
	}
}

void	print_x(t_info *f, unsigned int n, int base, char *list)
{
	int	i = 0;
	char	tab[99];

	while (1)
	{
		tab[i++] = list[n % base];
		n /= base;
		if (n == 0)
			break ;
	}
	while (i--)
		ft_putchar(&*f, tab[i]);
}

void	parse_format(t_info *f, char c, va_list va)
{
	if (c == 's')
		print_s(&*f, va_arg(va, char *));
	if (c == 'd')
		print_d(&*f, va_arg(va, int));
	if (c == 'x')
		print_x(&*f, va_arg(va, unsigned int), 16, "0123456789abcdef");
	else if (c != '%' && c != 's'&& c != 'd' && c != 'x')
		ft_putchar(*&f, c);
}

int	ft_printf(const char *format, ...)
{
	t_info	f;
	va_list	va;

	va_start(va, format);
	f.i = -1;
	f.ret = 0;
	if (!format)
		return (0);
	while (format[++f.i])
	{
		if (format[f.i] == '%')
			parse_format(&f, format[++f.i], va);
		else
			ft_putchar(&f, format[f.i]);
	}
	if (!format)
		return (0);
	va_end(va);
	return (f.ret);
}

/*int	main()
{
	int	a = 0;
	int	b = 0;
	int	n = 12;
	char *s = "bonjour, ca va ?";

	a = ft_printf("1 : print_s = [%s], print_d = [%d], print_x = [%x]\n", s, n, n);
	b = printf("2 : print_s = [%s], print_d = [%d], print_x = [%x]\n", s, n, n);
	printf("1 = [%d], 2 = [%d]\n", a, b);
	return (0);
}*/
