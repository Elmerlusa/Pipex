/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 20:36:12 by javmarti          #+#    #+#             */
/*   Updated: 2022/09/23 20:36:12 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printstr(char const *s)
{
	int	print_len;

	print_len = 0;
	if (s == 0)
		return (ft_printstr("(null)"));
	while (*s)
	{
		print_len += ft_printchar(*s);
		s++;
	}
	return (print_len);
}
