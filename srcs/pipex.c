/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:46:31 by javmarti          #+#    #+#             */
/*   Updated: 2022/12/11 17:22:10 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_child(char *infile, char *command, int *pipe_fd);
int	last_child(char *outfile, char *command, int *pipe_fd);

int main(int argc, char *argv[])
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;
	
	if (argc != 5 || check_access(argv[1], argv[argc - 1]) == 0)
		return (0);
	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
		first_child(argv[1], argv[2], pipe_fd);
	else
	{
		waitpid(pid, &status, 0);
		close(pipe_fd[WRITE_END]);
		pid = fork();
		if (pid == 0)
			last_child(argv[argc - 1], argv[3], pipe_fd);
		else
		{
			waitpid(pid, &status, 0);
			close(pipe_fd[READ_END]);
		}
	}
	return (0);
}

int	first_child(char *infile, char *command, int *pipe_fd)
{
	int		infile_fd;
	char	**args;
	char	*bin;

	infile_fd = open(infile, O_RDONLY);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
	close(pipe_fd[WRITE_END]);
	args = ft_split(command, ' ');
	bin = ft_strjoin("/usr/bin/", args[0]);
	execve(bin, args, NULL);
	perror("CHILD");
	free_split(args);
	free(bin);
	return (0);
}

int	last_child(char *outfile, char *command, int *pipe_fd)
{
	int		outfile_fd;
	char	**args;
	char	*bin;

	dup2(pipe_fd[READ_END], STDIN_FILENO);
	close(pipe_fd[READ_END]);
	outfile_fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	args = ft_split(command, ' ');
	bin = ft_strjoin("/usr/bin/", args[0]);
	execve(bin, args, NULL);
	perror("CHILD");
	free_split(args);
	free(bin);
	return (0);
}
