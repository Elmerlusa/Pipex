/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:46:31 by javmarti          #+#    #+#             */
/*   Updated: 2023/01/16 18:36:40 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_pipex pipex, char *envp[]);
void	last_child(t_pipex pipex, char *envp[]);
t_pipex	read_input(int argc, char *argv[], char *envp[], int *pipe_fd);
char	*here_doc(char *delimitator);

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	int		pipe_fd[2];
	int		status;

	if (argc < 5 || pipe(pipe_fd) < 0)
		perror_exit("Error");
	pipex = read_input(argc, argv, envp, pipe_fd);
	if ((access(pipex.outfile, F_OK) == 0 && access(pipex.outfile, W_OK) == -1)
		|| (pipex.delimiter == NULL && access(argv[1], R_OK) == -1))
		perror_exit("Error");
	first_child(pipex, envp);
	wait(&status);
	close(pipe_fd[WRITE_END]);
	last_child(pipex, envp);
	wait(&status);
	close(pipe_fd[READ_END]);
	return (0);
}

t_pipex	read_input(int argc, char *argv[], char *envp[], int *pipe_fd)
{
	t_pipex	pipex;

	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		pipex.delimiter = argv[2];
		pipex.infile = NULL;
	}
	else
	{
		pipex.delimiter = NULL;
		pipex.infile = argv[1];
	}
	pipex.outfile = argv[argc - 1];
	pipex.command1 = argv[argc - 3];
	pipex.command2 = argv[argc - 2];
	pipex.pipe_fd = pipe_fd;
	pipex.path = get_path_envp(envp);
	return (pipex);
}
