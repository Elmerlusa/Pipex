/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:46:31 by javmarti          #+#    #+#             */
/*   Updated: 2022/12/01 18:33:05 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	execute_command(char *command, char *file);

int main(int argc, char *argv[])
{
	char	*files[2];
	char	*commands[argc - 3];
	pid_t	pid;
	int		p[2];

	if (argc != 5)
		return (0);
	files[0] = argv[1];
	files[1] = argv[argc - 1];
	commands[0] = argv[2];
	commands[1] = argv[3];
	if (access(files[0], R_OK) == -1)
		perror("ERROR");



	pipe(p);
	close(p[0]);
	while (read(p[1], ))
	pid = fork();
	if (pid == 0)
		execute_command(commands[0], files[0]);
	return (0);
}

static int	execute_command(char *command, char *file)
{
	char	*pathfile;
	char	**args;

	ft_printf("%s\n", command);
	if (ft_strchr(command, ' ') == NULL)
	{
		args = (char **)ft_calloc(3, sizeof(char *));
		args[0] = command;
		args[1] = file;
		pathfile = ft_strjoin("/bin/", command);
		execve(pathfile, args, NULL);
		free(pathfile);
		free(args);
	}
	free(command);
	return (0);
}