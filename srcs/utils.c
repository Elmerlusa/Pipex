/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:04:04 by javmarti          #+#    #+#             */
/*   Updated: 2022/12/11 16:04:04 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	perror_exit(char *str)
{
	perror(str);
	exit(0);
}

char	*free_join(char *s1, char *s2)
{
	char	*s3;

	s3 = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (s3);
}

void	free_split(char **split)
{
	while (*split != NULL)
	{
		free(*split);
		(*split)++;
	}
	free(split);
	return ;
}

char	*get_path_envp(char *envp[])
{
	int		index;
	char	**path;

	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], "PATH", 4) == 0)
		{
			path = ft_split(envp[index], '=');
			free(path[0]);
			return (path[1]);
		}
		index++;
	}
	return (NULL);
}
