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

char	*get_bin_from_path(char *path);

static char	*here_doc(char *delimitator)
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

static int	open_infile(t_pipex pipex)
{
	int		infile_fd;
	char	*heredoc_input;

	if (pipex.heredoc_flag == 0)
		infile_fd = open(pipex.infile, O_RDONLY);
	else
	{
		infile_fd = open(".heredoc_temp", O_CREAT | O_WRONLY | O_TRUNC, \
			S_IRWXU);
		if (infile_fd == -1)
			perror_exit(".heredoc_temp", 0);
		heredoc_input = here_doc(pipex.delimiter);
		ft_putstr_fd(heredoc_input, infile_fd);
		free(heredoc_input);
		close(infile_fd);
		infile_fd = open(".heredoc_temp", O_RDONLY);
	}
	if (infile_fd == -1)
		perror_exit("Error infile", 1);
	return (infile_fd);
}

static int	open_outfile(t_pipex pipex)
{
	int	outfile_fd;

	if (pipex.heredoc_flag == 0)
		outfile_fd = open(pipex.outfile, O_CREAT | O_TRUNC | O_WRONLY, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		outfile_fd = open(pipex.outfile, O_CREAT | O_APPEND | O_WRONLY, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (outfile_fd == -1)
		perror_exit(pipex.outfile, 1);
	return (outfile_fd);
}

static void	dup_and_exec(int fd_2_stdin, int fd_2_stdout, t_pipex pipex)
{
	char	**args;

	dup2(fd_2_stdin, STDIN_FILENO);
	close(fd_2_stdin);
	if (access(".heredoc_temp", F_OK) == 0)
		unlink(".heredoc_temp");
	dup2(fd_2_stdout, STDOUT_FILENO);
	close(fd_2_stdout);
	args = ft_split(pipex.commands[pipex.index], ' ');
	if (args == NULL)
		perror_exit("malloc error", 0);
	if (args[0][0] == '/')
		args[0] = get_bin_from_path(args[0]);
	execve(pipex.binaries[pipex.index], args, pipex.envp);
}

int	create_child(t_pipex pipex)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid < 0)
		perror_exit("pid error", 0);
	else if (pid == 0)
	{
		if (pipex.index == 0)
			dup_and_exec(open_infile(pipex), pipex.pipes_fd[0][WRITE_END], \
			pipex);
		else if (pipex.index == pipex.comm_number - 1)
			dup_and_exec(pipex.pipes_fd[pipex.index - 1][READ_END], \
			open_outfile(pipex), pipex);
		else
			dup_and_exec(pipex.pipes_fd[pipex.index - 1][READ_END], \
			pipex.pipes_fd[pipex.index][WRITE_END], pipex);
	}
	else
		waitpid(pid, &status, 0);
	return (status);
}
