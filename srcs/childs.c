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
void	dup_and_exec(int fd_2_stdin, int fd_2_stdout, t_pipex pipex);

int	create_child(t_pipex pipex)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		perror_exit("pid error", 0);
	else if (pid == 0)
	{
		if (pipex.index == 0)
			dup_and_exec(open_infile(pipex), pipex.pipe_fd[WRITE_END], pipex);
		else if (pipex.index == 1)
			dup_and_exec(pipex.pipe_fd[READ_END], open_outfile(pipex), pipex);
	}
	else
		waitpid(pid, &status, 0);
	return (status);
}

void	exec_command(char *command, char **paths, char **envp)
{
	char	**args;
	char	*bin;
	int		index;

	args = ft_split(command, ' ');
	if (args == NULL)
		perror_exit("malloc args split error", 0);
	index = 0;
	while (paths[index])
	{
		bin = ft_strjoin(paths[index], args[0]);
		if (bin == NULL)
			perror_exit("malloc paths join error", 0);
		if (access(bin, X_OK) == 0)
			execve(bin, args, envp);
		free(bin);
		index++;
	}
	perror_exit(command, 0);
}

void	dup_and_exec(int fd_2_stdin, int fd_2_stdout, t_pipex pipex)
{
	dup2(fd_2_stdin, STDIN_FILENO);
	close(fd_2_stdin);
	unlink(".heredoc_temp");
	dup2(fd_2_stdout, STDOUT_FILENO);
	close(fd_2_stdout);
	exec_command(pipex.commands[pipex.index], pipex.paths, pipex.envp);
}
