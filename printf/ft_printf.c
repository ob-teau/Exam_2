/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alice <acoinus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 09:05:36 by alice             #+#    #+#             */
/*   Updated: 2022/02/14 11:32:36 by alice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(t_info *f, char c)
{
	if (write(1, &c, 1))
		f->ret++;
	return ;
}

int	print_s(t_info *f, char *s)
{
	int	i = -1;

	if (!s)
		return (-1);
	while (s[++i])
		ft_putchar(&*f, s[i]);
	return	(0);
}

int	print_d(t_info *f, int	n)
{
	if (!n)
		return (-1);
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
//	ft_putchar(*&f, n + 48);
	return (0);
}

int	print_x(t_info *f, unsigned long long n, unsigned long long base, char *list)
{
	int	i = 0;
	char	tab[99];

	if (!n)
		return (-1);
	while (1)
	{
		tab[i++] = list[n % base];
		n /= base;
		if (n == 0)
			break ;
	}
	while (i--)
		ft_putchar(&*f, tab[i]);
	return (0);
}

int	parse_format(t_info *f, char c, va_list va)
{
	if (c == 's')
		if (print_s(&*f, va_arg(va, char *)) == -1)
			return (-1);
	if (c == 'd')
		if (print_d(&*f, va_arg(va, int)) == -1)
			return (-1);
	if (c == 'x')
		if (print_x(&*f, va_arg(va, unsigned int), 16, "0123456789abcdef") == -1)
			return (-1);
	return (0);
}

int	ft_printf(const char *format, ...)
{
	t_info	f;
	va_list	va;

	va_start(va, format);
	f.i = -1;
	if (!format)
		return (0);
	while (format[++f.i])
	{
		if (format[f.i] == '%')
		{
			if (parse_format(&f, format[++f.i], va) < 0)
				return (-1);
		}
		else
			ft_putchar(&f, format[f.i]);
	}
	if (!format)
		return (0);
	va_end(va);
	return (f.ret);
}

int	main()
{
	int	a = 0;
	int	b = 0;
	int	n = 12;
	char *s = "bonjour, ca va ?";

	a = ft_printf("(1 : print_s = [%s], print_d = [%d], print_x = [%x], ok)", s, n, n);
	printf("\n");
	b = printf("(2 : print_s = [%s], print_d = [%d], print_x = [%x], ok)\n", s, n, n);
	printf("1 = [%d], 2 = [%d]\n", a, b);
	return (0);
}
