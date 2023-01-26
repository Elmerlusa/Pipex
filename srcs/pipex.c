/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:46:31 by javmarti          #+#    #+#             */
/*   Updated: 2023/01/26 15:40:47 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		create_child(t_pipex pipex);
t_pipex	read_input(int argc, char *argv[], char *envp[]);

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	int		status;

	if (argc < 5)
		exit (1);
	pipex = read_input(argc, argv, envp);
	if ((access(pipex.outfile, F_OK) == 0 && access(pipex.outfile, W_OK) == -1)
		|| (pipex.heredoc_flag == 0 && access(argv[1], R_OK) == -1))
		perror_exit("access error", 0);
	while (++pipex.index < 2)
	{
		status = create_child(pipex);
		if (status < 0)
			perror_exit("child error", status);
		if (pipex.index == 0)
			close(pipex.pipe_fd[WRITE_END]);
		else if (pipex.index == 1)
			close(pipex.pipe_fd[READ_END]);
	}
	exit(status);
}

int	*get_pipe_fd();

int	**get_pipes_fd(int count)
{
	int	**pipes_fd;
	int	index;

	pipes_fd = (int **)ft_calloc(count, sizeof(int *));
	if (pipes_fd == NULL)
		perror_exit("Error pipe", 1);
	index = 0;
	while (index < count)
		pipes_fd[index++] = get_pipe_fd();
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
	pipex.pipe_fd = get_pipe_fd();
	pipex.envp = envp;
	pipex.paths = get_paths_envp(envp);
	if (pipex.paths == NULL)
		perror_exit("malloc get paths error", 0);
	pipex.index = -1;
	return (pipex);
}

int	*get_pipe_fd()
{
	int	*pipe_fd;

	pipe_fd = (int *)ft_calloc(2, sizeof(int));
	if (pipe_fd == NULL || pipe(pipe_fd) < 0)
		perror_exit("Pipe error", 1);
	return pipe_fd;
}