/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:46:31 by javmarti          #+#    #+#             */
/*   Updated: 2023/01/25 18:20:11 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		create_child(t_pipex pipex);
t_pipex	read_input(int argc, char *argv[], char *envp[], int *pipe_fd);

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	int		pipe_fd[2];
	int		status;

	if (argc < 5 || pipe(pipe_fd) < 0)
		exit (1);
	pipex = read_input(argc, argv, envp, pipe_fd);
	if ((access(pipex.outfile, F_OK) == 0 && access(pipex.outfile, W_OK) == -1)
		|| (pipex.heredoc_flag == 0 && access(argv[1], R_OK) == -1))
		perror_exit("access error", 0);
	while (++pipex.index < 2)
	{
		status = create_child(pipex);
		if (status < 0)
			perror_exit("child error", status);
		if (pipex.index == 0)
			close(pipe_fd[WRITE_END]);
		else if (pipex.index == 1)
			close(pipe_fd[READ_END]);
	}
	exit(status);
}

t_pipex	read_input(int argc, char *argv[], char *envp[], int *pipe_fd)
{
	t_pipex	pipex;

	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		pipex.heredoc_flag = 1;
		pipex.delimiter = argv[2];
		pipex.infile = NULL;
	}
	else
	{
		pipex.heredoc_flag = 0;
		pipex.delimiter = NULL;
		pipex.infile = argv[1];
	}
	pipex.outfile = argv[argc - 1];
	pipex.commands = argv + 2 + pipex.heredoc_flag;
	pipex.pipe_fd = pipe_fd;
	pipex.paths = get_paths_envp(envp);
	if (pipex.paths == NULL)
		perror_exit("malloc get paths error", 0);
	pipex.envp = envp;
	pipex.index = -1;
	pipex.comm_number = argc - 3 - pipex.heredoc_flag;
	return (pipex);
}
