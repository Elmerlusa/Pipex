/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 19:06:54 by javmarti          #+#    #+#             */
/*   Updated: 2022/09/18 19:06:54 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	char			*str;
	unsigned int	index;
	unsigned int	len;

	if (s1 == NULL)
		return (NULL);
	index = 0;
	while (s1[index] && ft_strchr(set, s1[index]))
		index++;
	len = ft_strlen(s1);
	while (len > 0 && ft_strrchr(set, s1[len - 1]))
		len--;
	if (len == 0)
		index = 0;
	str = ft_substr(s1, index, len - index);
	return (str);
}
