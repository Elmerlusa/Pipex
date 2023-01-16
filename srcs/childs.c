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

char	*here_doc(char *delimitator)
{
	char	*text;
	char	*line;

	text = (char *)ft_calloc(1, sizeof(char));
	ft_printf("> ");
	line = get_next_line(STDIN_FILENO);
	while (ft_strncmp(line, delimitator, ft_strlen(delimitator) - 1) != 0)
	{
		ft_printf("> ");
		text = free_join(text, line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	return (text);
}

void	input_to_stdin(t_pipex pipex)
{
	int		infile_fd;
	char	*heredoc_input;

	if (pipex.delimiter == NULL)
		infile_fd = open(pipex.infile, O_RDONLY);
	else
	{
		infile_fd = open(".heredoc_temp", O_CREAT | O_WRONLY | O_TRUNC, \
			S_IRWXU);
		if (infile_fd == -1)
			perror_exit("Error");
		heredoc_input = here_doc(pipex.delimiter);
		ft_putstr_fd(heredoc_input, infile_fd);
		free(heredoc_input);
		close(infile_fd);
		infile_fd = open(".heredoc_temp", O_RDONLY);
	}
	if (infile_fd == -1)
		perror_exit("Error");
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	if (pipex.delimiter != NULL)
		unlink(".heredoc_temp");
	return ;
}

void	exec_command(char *command, char **paths, char *envp[])
{
	char	**args;
	char	*bin;
	int		index;

	args = ft_split(command, ' ');
	if (args == NULL)
		perror_exit("Error");
	index = 0;
	while (paths[index])
	{
		bin = ft_strjoin(paths[index], args[0]);
		if (access(bin, X_OK) == 0)
			execve(bin, args, envp);
		free(bin);
		index++;
	}
	perror_exit("Error");
}

void	first_child(t_pipex pipex, char *envp[])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror_exit("Error");
	else if (pid == 0)
	{
		input_to_stdin(pipex);
		dup2(pipex.pipe_fd[WRITE_END], STDOUT_FILENO);
		close(pipex.pipe_fd[WRITE_END]);
		exec_command(pipex.command1, pipex.paths, envp);
	}
	return ;
}

void	last_child(t_pipex pipex, char *envp[])
{
	pid_t	pid;
	int		outfile_fd;

	pid = fork();
	if (pid < 0)
		perror_exit("Error");
	else if (pid == 0)
	{
		dup2(pipex.pipe_fd[READ_END], STDIN_FILENO);
		close(pipex.pipe_fd[READ_END]);
		if (pipex.delimiter == NULL)
			outfile_fd = open(pipex.outfile, O_CREAT | O_TRUNC | O_WRONLY, \
				S_IRWXU);
		else
			outfile_fd = open(pipex.outfile, O_CREAT | O_APPEND | O_WRONLY, \
				S_IRWXU);
		if (outfile_fd == -1)
			perror_exit("Error");
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
		exec_command(pipex.command2, pipex.paths, envp);
	}
	return ;
}
