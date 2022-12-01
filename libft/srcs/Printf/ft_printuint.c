/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printudec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:20:35 by javmarti          #+#    #+#             */
/*   Updated: 2022/09/26 19:20:35 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printuint(unsigned int n)
{
	int	print_len;

	print_len = 0;
	if (n >= 10)
		print_len += ft_printuint(n / 10);
	print_len += ft_printchar((n % 10) + '0');
	return (print_len);
}
