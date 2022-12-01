/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 19:15:31 by javmarti          #+#    #+#             */
/*   Updated: 2022/09/18 19:15:31 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	index1;
	size_t	index2;

	if (haystack == 0 && len == 0)
		return (NULL);
	if (needle[0] == '\0')
		return ((char *)haystack);
	index1 = 0;
	while (index1 <= len && haystack[index1])
	{
		if (haystack[index1] == needle[0])
		{
			index2 = 0;
			while (haystack[index1 + index2] && needle[index2])
			{
				if (haystack[index1 + index2] != needle[index2])
					break ;
				index2++;
			}
			if (needle[index2] == '\0' && index1 + index2 <= len)
				return ((char *)&haystack[index1]);
		}
		index1++;
	}
	return (NULL);
}
