/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:40:00 by javmarti          #+#    #+#             */
/*   Updated: 2022/11/30 15:40:00 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# define READ_END 0
# define WRITE_END 1

typedef struct s_pipex
{
	int		heredoc_flag;
	char	*delimiter;
	char	*infile;
	char	*outfile;
	char	*command1;
	char	*command2;
	int		*pipe_fd;
	char	**paths;
	char	**envp;
}	t_pipex;

char	**get_paths_envp(char *envp[]);
char	*free_join(char *s1, char *s2);
void	free_split(char **split);
void	perror_exit(char *str);

#endif