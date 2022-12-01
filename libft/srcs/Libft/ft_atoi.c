/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 19:14:10 by javmarti          #+#    #+#             */
/*   Updated: 2022/09/18 19:14:10 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(int c);
static int	get_sign(char **str);

int	ft_atoi(const char *str)
{
	int				sign;
	long int		num;

	if (*str == '\0' || str == 0)
		return (0);
	while (is_space(*str))
		str++;
	sign = get_sign((char **)&str);
	num = 0;
	while (*str && ft_isdigit(*str))
	{
		if (num * sign > 9223372036854775807 / 10)
			return (-1);
		if (num * sign < -9223372036854775807 / 10)
			return (0);
		num *= 10;
		num += *(str++) - '0';
	}
	return (num * sign);
}

static int	get_sign(char **str)
{
	if (*(*str) == '-')
	{
		(*str)++;
		return (-1);
	}
	else if (*(*str) == '+')
		(*str)++;
	return (1);
}

static int	is_space(int c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\f' || c == '\v' || c == '\r')
		return (1);
	return (0);
}
