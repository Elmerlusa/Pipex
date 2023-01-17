/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:46:31 by javmarti          #+#    #+#             */
/*   Updated: 2023/01/17 16:22:28 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		create_child(t_pipex pipex, int index);
t_pipex	read_input(int argc, char *argv[], char *envp[], int *pipe_fd);

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	int		pipe_fd[2];
	int		index;

	if (argc < 5 || pipe(pipe_fd) < 0)
		perror_exit("pipe or input error");
	pipex = read_input(argc, argv, envp, pipe_fd);
	if ((access(pipex.outfile, F_OK) == 0 && access(pipex.outfile, W_OK) == -1)
		|| (pipex.heredoc_flag == 0 && access(argv[1], R_OK) == -1))
		perror_exit("access error");
	index = -1;
	while (++index < 2)
	{
		if (create_child(pipex, index) < 0)
			perror_exit("child error");
		if (index == 0)
			close(pipe_fd[WRITE_END]);
		else if (index == 1)
			close(pipe_fd[READ_END]);
	}
	if (pipex.heredoc_flag == 1)
		unlink(".heredoc_temp");
	return (0);
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
	pipex.command1 = argv[argc - 3];
	pipex.command2 = argv[argc - 2];
	pipex.pipe_fd = pipe_fd;
	pipex.paths = get_paths_envp(envp);
	if (pipex.paths == NULL)
		perror_exit("malloc get paths error");
	pipex.envp = envp;
	return (pipex);
}
