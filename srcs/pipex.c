/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:46:31 by javmarti          #+#    #+#             */
/*   Updated: 2023/01/11 18:29:41 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(char *infile, char *command, int *pipe_fd, char *envp[]);
void	last_child(char *outfile, char *command, int *pipe_fd, char *envp[]);

int	main(int argc, char *argv[], char *envp[])
{
	int	pipe_fd[2];
	int	status;

	if (argc != 5 || check_access(argv[1], argv[argc - 1]) == 0)
		return (0);
	if (pipe(pipe_fd) < 0)
	{
		perror("Error");
		return (0);
	}
	first_child(argv[1], argv[2], pipe_fd, envp);
	waitpid(-1, &status, 0);
	close(pipe_fd[WRITE_END]);
	last_child(argv[argc - 1], argv[3], pipe_fd, envp);
	waitpid(-1, &status, 0);
	close(pipe_fd[READ_END]);
	return (0);
}

void	exec_command(char *command, char *envp[])
{
	char	**args;
	char	**paths;
	char	*path;
	char	*bin;
	int		index;

	args = ft_split(command, ' ');
	paths = ft_split(get_path_envp(envp), ':');
	index = 0;
	while (paths[index])
	{
		path = ft_strjoin(paths[index], "/");
		bin = ft_strjoin(path, args[0]);
		free(path);
		if (access(bin, X_OK) == 0)
			execve(bin, args, envp);
		free(bin);
		index++;
	}
	perror("CHILD");
	exit(0);
}

void	first_child(char *infile, char *command, int *pipe_fd, char *envp[])
{
	int		infile_fd;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Error");
		exit(0);
	}
	if (pid == 0)
	{
		infile_fd = open(infile, O_RDONLY);
		if (infile_fd == -1)
		{
			perror("Error");
			exit(0);
		}
		dup2(infile_fd, STDIN_FILENO);
		close(infile_fd);
		dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
		close(pipe_fd[WRITE_END]);
		exec_command(command, envp);
	}
	return ;
}

void	last_child(char *outfile, char *command, int *pipe_fd, char *envp[])
{
	int		outfile_fd;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Error");
		exit(0);
	}
	if (pid == 0)
	{
		dup2(pipe_fd[READ_END], STDIN_FILENO);
		close(pipe_fd[READ_END]);
		outfile_fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);
		if (outfile_fd == -1)
		{
			perror("Error");
			exit(0);
		}
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
		exec_command(command, envp);
	}
	return ;
}
