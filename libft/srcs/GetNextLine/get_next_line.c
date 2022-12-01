/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javmarti <javmarti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:37:22 by javmarti          #+#    #+#             */
/*   Updated: 2022/10/13 14:37:22 by javmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_line(char *line, char *buffer);
char	*read_buffer(int fd, char *buffer, char *line);
void	update_buffer(char *buffer);

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = (char *)ft_calloc(1, sizeof(char));
	if (buffer == NULL)
		buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	else
		line = join_line(line, buffer);
	line = read_buffer(fd, buffer, line);
	if (line == NULL || *line == '\0')
	{
		free(line);
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	update_buffer(buffer);
	return (line);
}

char	*join_line(char *line, char *buffer)
{
	char	*new_line;
	char	*aux;
	char	*aux_line;

	if (buffer == NULL || line == NULL)
	{
		free(line);
		return (NULL);
	}
	aux = ft_strchr(buffer, '\n');
	if (aux == NULL)
		new_line = ft_strjoin(line, buffer);
	else
	{
		aux_line = ft_substr(buffer, 0, aux + 1 - buffer);
		new_line = ft_strjoin(line, aux_line);
		free(aux_line);
	}
	free(line);
	return (new_line);
}

char	*read_buffer(int fd, char *buffer, char *line)
{
	int		bytes_read;

	if (line == NULL || buffer == NULL)
	{
		free(line);
		return (NULL);
	}
	if (ft_strchr(line, '\n') != NULL)
		return (line);
	bytes_read = 1;
	while (bytes_read > 0 && ft_strchr(buffer, '\n') == NULL)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(line);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		line = join_line(line, buffer);
		if (line == NULL)
			break ;
	}
	return (line);
}

void	update_buffer(char *buffer)
{
	char	*aux;
	size_t	index;

	aux = ft_strchr(buffer, '\n');
	if (aux == NULL)
		buffer[0] = '\0';
	else
	{
		aux++;
		index = -1;
		while (aux[++index])
			buffer[index] = aux[index];
		buffer[index] = '\0';
	}
	return ;
}
