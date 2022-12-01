/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 19:15:34 by javmarti          #+#    #+#             */
/*   Updated: 2022/09/18 19:15:34 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	index;

	index = ft_strlen(s);
	while (index > 0)
	{
		if (s[index] == (char)c)
			return ((char *)(s + index));
		index--;
	}
	if (s[index] == (char)c)
		return ((char *)(s + index));
	return (NULL);
}
