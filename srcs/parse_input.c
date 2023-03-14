/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:16:50 by javmarti          #+#    #+#             */
/*   Updated: 2023/02/25 12:16:50 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	**get_pipes_fd(int count)
{
	int	**pipes_fd;
	int	index;

	pipes_fd = (int **)ft_calloc(count + 1, sizeof(int *));
	if (pipes_fd == NULL)
		perror_exit("Error pipe", 1);
	index = 0;
	while (index < count)
	{
		pipes_fd[index] = (int *)ft_calloc(2, sizeof(int));
		if (pipes_fd[index] == NULL || pipe(pipes_fd[index]) < 0)
			perror_exit("Pipe error", 1);
		index++;
	}
	return (pipes_fd);
}

char	*get_binary(char *command, char **paths)
{
	char	*bin;
	int		index;

	index = -1;
	while (paths[++index])
	{
		bin = ft_strjoin(paths[index], command);
		if (bin == NULL)
			return (NULL);
		if (access(bin, X_OK) == 0)
			return (bin);
		free(bin);
	}
	return (NULL);
}

char	**get_binaries(char **commands, int comm_number, char *envp[])
{
	char	**binaries;
	char	**paths;
	char	**command;
	int		index;

	binaries = (char **)ft_calloc(comm_number + 1, sizeof(char *));
	if (binaries == NULL)
		return (NULL);
	paths = get_paths_envp(envp);
	index = -1;
	while (++index < comm_number)
	{
		command = ft_split(commands[index], ' ');
		binaries[index] = get_binary(command[0], paths);
		free_split(command);
		if (binaries[index] == NULL)
		{
			free_split(paths);
			free_split(binaries);
			return (NULL);
		}
	}
	free_split(paths);
	return (binaries);
}

void	parse_redir(int argc, char *argv[], t_pipex *pipex)
{
	pipex->heredoc_flag = 0;
	pipex->delimiter = NULL;
	pipex->infile = NULL;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0
		&& ft_strlen(argv[1]) == ft_strlen("here_doc"))
	{
		pipex->heredoc_flag = 1;
		pipex->delimiter = argv[2];
	}
	else
		pipex->infile = argv[1];
	pipex->outfile = argv[argc - 1];
}

t_pipex	parse_input(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	parse_redir(argc, argv, &pipex);
	pipex.commands = argv + 2 + pipex.heredoc_flag;
	pipex.comm_number = argc - 3 - pipex.heredoc_flag;
	pipex.pipes_fd = get_pipes_fd(pipex.comm_number - 1);
	pipex.envp = envp;
	pipex.binaries = get_binaries(pipex.commands, pipex.comm_number, envp);
	if (pipex.binaries == NULL)
	{
		free_pipex(pipex);
		perror_exit("command not found", 0);
	}
	pipex.index = -1;
	return (pipex);
}
