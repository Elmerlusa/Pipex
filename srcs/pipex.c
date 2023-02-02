/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:46:31 by javmarti          #+#    #+#             */
/*   Updated: 2023/02/02 19:24:55 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		create_child(t_pipex pipex);
t_pipex	read_input(int argc, char *argv[], char *envp[]);
void	free_pipex(t_pipex pipex);
void	close_fds(t_pipex pipex);

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	int		status;

	if (argc < 5)
		exit (1);
	pipex = read_input(argc, argv, envp);
	if ((access(pipex.outfile, F_OK) == 0 && access(pipex.outfile, W_OK) == -1)
		|| (pipex.heredoc_flag == 0 && access(argv[1], R_OK) == -1))
	{
		free_pipex(pipex);
		perror_exit("access error", 0);
	}
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

int	**get_pipes_fd(int count)
{
	int	**pipes_fd;
	int	index;

	pipes_fd = (int **)ft_calloc(count + 1, sizeof(int *));
	if (pipes_fd == NULL)
		perror_exit("Error pipe", 1);
	index = 0;
	while (index < count)
	{
		pipes_fd[index] = (int *)ft_calloc(2, sizeof(int));
		if (pipes_fd[index] == NULL || pipe(pipes_fd[index]) < 0)
			perror_exit("Pipe error", 1);
		index++;
	}
	return (pipes_fd);
}

t_pipex	read_input(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	pipex.heredoc_flag = 0;
	pipex.delimiter = NULL;
	pipex.infile = NULL;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		pipex.heredoc_flag = 1;
		pipex.delimiter = argv[2];
	}
	else
		pipex.infile = argv[1];
	pipex.outfile = argv[argc - 1];
	pipex.commands = argv + 2 + pipex.heredoc_flag;
	pipex.comm_number = argc - 3 - pipex.heredoc_flag;
	pipex.pipes_fd = get_pipes_fd(pipex.comm_number - 1);
	pipex.envp = envp;
	pipex.paths = get_paths_envp(envp);
	if (pipex.paths == NULL)
		perror_exit("malloc get paths error", 0);
	pipex.index = -1;
	return (pipex);
}

void	free_pipex(t_pipex pipex)
{
	int	index;

	index = -1;
	while (pipex.pipes_fd[++index])
		free(pipex.pipes_fd[index]);
	free(pipex.pipes_fd);
}
