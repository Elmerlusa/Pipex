/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 20:59:06 by javmarti          #+#    #+#             */
/*   Updated: 2022/09/23 20:59:06 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printhex(unsigned int n, char c)
{
	int	print_len;

	print_len = 0;
	if (n >= 16)
		print_len += ft_printhex(n / 16, c);
	if (c == 'x')
		print_len += ft_printchar("0123456789abcdef"[n % 16]);
	else
		print_len += ft_printchar("0123456789ABCDEF"[n % 16]);
	return (print_len);
}
