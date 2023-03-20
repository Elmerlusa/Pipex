/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:46:31 by javmarti          #+#    #+#             */
/*   Updated: 2023/03/20 13:06:43 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	int		status;

	if (argc < 5)
	{
		ft_putstr_fd("Wrong number of args\n", STDERR_FILENO);
		exit (1);
	}
	pipex = parse_input(argc, argv, envp);
	status = 0;
	while (++pipex.index < pipex.comm_number)
	{
		status = create_child(pipex);
		if (status < 0)
		{
			free_pipex(pipex);
			perror_exit("child error", status);
		}
		close_fds(pipex);
	}
	free_pipex(pipex);
	exit(status);
}

void	close_fds(t_pipex pipex)
{
	if (pipex.index == 0)
		close(pipex.pipes_fd[0][WRITE_END]);
	else if (pipex.index == pipex.comm_number - 1)
		close(pipex.pipes_fd[pipex.index - 1][READ_END]);
	else
	{
		close(pipex.pipes_fd[pipex.index - 1][READ_END]);
		close(pipex.pipes_fd[pipex.index][WRITE_END]);
	}
	return ;
}

void	free_pipex(t_pipex pipex)
{
	int	index;

	index = -1;
	while (pipex.pipes_fd[++index])
		free(pipex.pipes_fd[index]);
	free(pipex.pipes_fd);
	return ;
}

char	*get_bin_from_path(char *path)
{
	char	*bin;
	char	**split;
	int		index;

	split = ft_split(path, '/');
	free(path);
	if (split == NULL)
		return (NULL);
	index = -1;
	while (split[++index + 1])
		;
	bin = ft_strdup(split[index]);
	free_split(split);
	return (bin);
}
