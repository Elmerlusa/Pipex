/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:50:14 by javmarti          #+#    #+#             */
/*   Updated: 2023/01/17 15:50:14 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	open_infile(t_pipex pipex)
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

int	open_outfile(t_pipex pipex)
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
