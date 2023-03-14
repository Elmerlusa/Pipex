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

void	perror_exit(char *str, int status)
{
	perror(str);
	exit(status);
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
	int	index;

	index = -1;
	while (split[++index])
		free(split[index]);
	free(split);
	return ;
}

char	*get_path_envp(char *envp[])
{
	int		index;
	char	**path;
	char	*ptr;

	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], "PATH", 4) == 0)
		{
			path = ft_split(envp[index], '=');
			ptr = path[1];
			free(path[0]);
			free(path);
			return (ptr);
		}
		index++;
	}
	return (NULL);
}

char	**get_paths_envp(char *envp[])
{
	char	*path;
	char	**path_splitted;
	int		index;
	char	*aux;

	path = get_path_envp(envp);
	if (path == NULL)
		perror_exit("malloc path error", 0);
	path_splitted = ft_split(path, ':');
	free(path);
	if (path_splitted == NULL)
		perror_exit("malloc path splitted error", 0);
	index = -1;
	while (path_splitted[++index])
	{
		aux = ft_strjoin(path_splitted[index], "/");
		if (aux == NULL)
		{
			free_split(path_splitted);
			perror_exit("malloc join error", 0);
		}
		free(path_splitted[index]);
		path_splitted[index] = aux;
	}
	return (path_splitted);
}
