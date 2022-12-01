/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:47:45 by javmarti          #+#    #+#             */
/*   Updated: 2022/09/27 18:47:45 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

static int	handle_percentage(char const c, va_list arg);

int	ft_printf(char const *str, ...)
{
	int		print_len;
	va_list	arg;

	if (str == 0)
		return (-1);
	if (*str == '\0')
		return (0);
	va_start(arg, str);
	print_len = 0;
	while (*str)
	{
		if (*str == '%')
			print_len += handle_percentage(*(++str), arg);
		else
			print_len += ft_printchar(*str);
		str++;
	}
	va_end(arg);
	return (print_len);
}

static int	handle_percentage(char const c, va_list arg)
{
	if (c == 'c')
		return (ft_printchar(va_arg(arg, int)));
	else if (c == 's')
		return (ft_printstr(va_arg(arg, char const *)));
	else if (c == 'p')
		return (ft_printptr(va_arg(arg, void *)));
	else if (c == 'i' || c == 'd')
		return (ft_printint(va_arg(arg, int)));
	else if (c == 'u')
		return (ft_printuint(va_arg(arg, unsigned int)));
	else if (c == 'x' || c == 'X')
		return (ft_printhex(va_arg(arg, unsigned int), c));
	else if (c == '%')
		return (ft_printchar(c));
	else
	{
		ft_printchar('%');
		ft_printchar(c);
		return (2);
	}
}
