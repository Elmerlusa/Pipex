/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:46:31 by javmarti          #+#    #+#             */
/*   Updated: 2022/12/11 14:51:55 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[])
{
	pid_t	pid;
	int		fd[2];
	char	*pathfile1, *pathfile2;
	char	**args1, **args2;
	int		start_fd, end_fd;
	int		status;
	
	if (argc != 5 || access(argv[1], R_OK) == -1)
		return (0);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		start_fd = open(argv[1], O_RDONLY);
		dup2(start_fd, STDIN_FILENO);
		close(start_fd);
		close(fd[READ_END]);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		args1 = ft_split(argv[2], ' ');
		pathfile1 = ft_strjoin("/usr/bin/", args1[0]);
		execve(pathfile1, args1, NULL);
	}
	else
	{
		waitpid(pid, &status, 0);
		close(fd[WRITE_END]);
		pid = fork();
		if (pid == 0)
		{
			dup2(fd[READ_END], STDIN_FILENO);
			close(fd[READ_END]);
			end_fd = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);
			dup2(end_fd, STDOUT_FILENO);
			close(end_fd);
			args2 = ft_split(argv[3], ' ');
			pathfile2 = ft_strjoin("/usr/bin/", args2[0]);
			execve(pathfile2, args2, NULL);
		}
		else
		{
			waitpid(pid, &status, 0);
			close(fd[READ_END]);
		}
	}
	return (0);
}
