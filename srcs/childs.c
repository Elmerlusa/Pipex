/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:20:17 by javmarti          #+#    #+#             */
/*   Updated: 2023/01/16 17:20:17 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		open_infile(t_pipex pipex);
int		open_outfile(t_pipex pipex);
void	dup_and_exec(int fd_2_stdin, int fd_2_stdout, t_pipex pipex, \
	char *command);

int	create_child(t_pipex pipex, int index)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		perror_exit("pid error", 0);
	else if (pid == 0)
	{
		if (index == 0)
			dup_and_exec(open_infile(pipex), pipex.pipe_fd[WRITE_END], \
				pipex, pipex.command1);
		else if (index == 1)
			dup_and_exec(pipex.pipe_fd[READ_END], open_outfile(pipex), \
				pipex, pipex.command2);
	}
	else
		waitpid(pid, &status, 0);
	return (status);
}
