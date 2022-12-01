/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 19:21:30 by javmarti          #+#    #+#             */
/*   Updated: 2022/09/18 19:21:30 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;
	size_t	len;

	len = count * size;
	if (len && len / count != size && count != 0)
		return (NULL);
	mem = malloc(len);
	if (mem == NULL)
		return (NULL);
	ft_bzero(mem, len);
	return (mem);
}
