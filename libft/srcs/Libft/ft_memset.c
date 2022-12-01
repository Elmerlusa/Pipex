/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 19:14:55 by javmarti          #+#    #+#             */
/*   Updated: 2022/09/18 19:14:55 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	index;

	if (len == 0)
		return (b);
	index = 0;
	while (index < len)
		((unsigned char *)b)[index++] = (unsigned char)c;
	return (b);
}
