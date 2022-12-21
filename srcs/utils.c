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

int	check_access(char *infile, char *outfile)
{
	if (access(infile, R_OK) == -1)
	{
		perror(infile);
		return (0);
	}
	if (access(outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
	{
		perror(outfile);
		return (0);
	}
	return (1);
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
