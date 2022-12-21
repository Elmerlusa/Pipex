/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:46:31 by javmarti          #+#    #+#             */
/*   Updated: 2022/12/21 13:07:54 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_child(char *infile, char *command, int *pipe_fd, char *envp[]);
int	last_child(char *outfile, char *command, int *pipe_fd, char *envp[]);

int	main(int argc, char *argv[], char *envp[])
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;

	if (argc != 5 || check_access(argv[1], argv[argc - 1]) == 0)
		return (0);
	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
		first_child(argv[1], argv[2], pipe_fd, envp);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		close(pipe_fd[WRITE_END]);
		pid = fork();
		if (pid == 0)
			last_child(argv[argc - 1], argv[3], pipe_fd, envp);
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
			close(pipe_fd[READ_END]);
		}
		else
			perror("Error");
	}
	else
		perror("Error");
	return (0);
}

int	exec_command(char *command, char *envp[])
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
	exit(-1);
}

int	first_child(char *infile, char *command, int *pipe_fd, char *envp[])
{
	int		infile_fd;

	infile_fd = open(infile, O_RDONLY);
	if (infile_fd == -1)
	{
		perror("Error");
		return (-1);
	}
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
	close(pipe_fd[WRITE_END]);
	return (exec_command(command, envp));
}

int	last_child(char *outfile, char *command, int *pipe_fd, char *envp[])
{
	int		outfile_fd;

	dup2(pipe_fd[READ_END], STDIN_FILENO);
	close(pipe_fd[READ_END]);
	outfile_fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);
	if (outfile_fd == -1)
	{
		perror("Error");
		return (-1);
	}
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	return (exec_command(command, envp));
}
