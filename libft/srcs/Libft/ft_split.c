/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 19:05:07 by javmarti          #+#    #+#             */
/*   Updated: 2022/09/18 19:05:07 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

static size_t	word_count(char const *s, char c);
static void		fill_split(char const *s, char c, char **split);
static void		free_split(char **split, size_t wc);

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	wc;

	if (s == NULL)
		return (NULL);
	wc = word_count(s, c);
	split = (char **)ft_calloc(wc + 1, sizeof(char *));
	if (split == NULL)
		return (NULL);
	fill_split(s, c, split);
	free_split(split, wc);
	return (split);
}

static void	free_split(char **split, size_t wc)
{
	size_t	index;

	index = 0;
	while (index < wc)
	{
		if (split[index++] != 0)
			continue ;
		index = 0;
		while (index < wc)
		{
			if (split[index] != 0)
				free(split[index]);
			index++;
		}
		free(split);
	}
	return ;
}

static void	fill_split(char const *s, char c, char **split)
{
	size_t	index;
	char	*s_aux;

	if (*s == 0)
		return ;
	if (c == '\0')
	{
		split[0] = ft_strdup(s);
		return ;
	}
	index = 0;
	s_aux = ft_strchr(s, c);
	while (s_aux)
	{
		if (s_aux - s > 0)
			split[index++] = ft_substr(s, 0, s_aux - s);
		s = s_aux + 1;
		s_aux = ft_strchr(s, c);
	}
	if (ft_strlen(s) > 0)
		split[index] = ft_strdup(s);
	return ;
}

static size_t	word_count(char const *s, char c)
{
	char	*s_aux;
	size_t	wc;

	if (*s == 0)
		return (0);
	if (c == '\0')
		return (1);
	s_aux = ft_strchr(s, c);
	wc = 0;
	while (s_aux)
	{
		if (s_aux - s > 0)
			wc++;
		s = s_aux + 1;
		s_aux = ft_strchr(s, c);
	}
	if (ft_strlen(s) > 0)
		wc++;
	return (wc);
}
