/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 13:16:37 by javmarti          #+#    #+#             */
/*   Updated: 2022/09/24 13:16:37 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printint(int n)
{
	int	print_len;

	print_len = 0;
	if (n == -2147483648)
	{
		print_len += ft_printstr("-2147483648");
		return (print_len);
	}
	else if (n < 0)
	{
		print_len += ft_printchar('-');
		n = -n;
	}
	if (n >= 10)
		print_len += ft_printint(n / 10);
	print_len += ft_printchar((n % 10) + '0');
	return (print_len);
}
