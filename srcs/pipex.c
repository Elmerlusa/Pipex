/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:46:31 by javmarti          #+#    #+#             */
/*   Updated: 2023/02/25 13:02:28 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	int		status;

	if (argc < 5)
		exit (1);
	pipex = parse_input(argc, argv, envp);
	if ((access(pipex.outfile, F_OK) == 0 && access(pipex.outfile, W_OK) == -1)
		|| (pipex.heredoc_flag == 0 && access(argv[1], R_OK) == -1))
	{
		free_pipex(pipex);
		perror_exit("access error", 0);
	}
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
}
