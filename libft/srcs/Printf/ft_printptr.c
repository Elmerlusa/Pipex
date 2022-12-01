/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 13:17:34 by javmarti          #+#    #+#             */
/*   Updated: 2022/09/24 13:17:34 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	printulonghex(unsigned long long n);

int	ft_printptr(void *ptr)
{
	return (ft_printstr("0x") + printulonghex((unsigned long long)ptr));
}

static int	printulonghex(unsigned long long n)
{
	int	print_len;

	print_len = 0;
	if (n >= 16)
		print_len += printulonghex(n / 16);
	print_len += ft_printchar("0123456789abcdef"[n % 16]);
	return (print_len);
}
