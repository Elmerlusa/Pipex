/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 19:04:34 by javmarti          #+#    #+#             */
/*   Updated: 2022/09/18 19:04:34 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_len(int n);
static void	store_num(int n, char **num, int len);

char	*ft_itoa(int n)
{
	char	*num;
	int		len;

	len = num_len(n);
	num = (char *)ft_calloc(len + 1, sizeof(char));
	if (num == NULL)
		return (NULL);
	store_num(n, &num, len);
	return (num);
}

static void	store_num(int n, char **num, int len)
{
	int	end;

	end = 0;
	if (n == -2147483648)
	{
		ft_strlcpy(*num, "-2147483648", len + 1);
		return ;
	}
	else if (n < 0)
	{
		(*num)[0] = '-';
		n = -n;
		end = 1;
	}
	while (len > end)
	{
		(*num)[len - 1] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	return ;
}

static int	num_len(int n)
{
	unsigned int	len;

	len = 0;
	if (n == -2147483648)
		return (11);
	if (n <= 0)
	{
		n = -n;
		len = 1;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}
