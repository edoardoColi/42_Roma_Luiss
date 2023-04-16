/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:06:53 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 14:22:46 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*set_buffer_pos(char *buffer)
{
	char	*str;
	int		i;
	int		j;

	i = line_len_n(buffer);
	if (!buffer[i] || !buffer)
		return (free_buffer(buffer));
	str = malloc(sizeof(char *) * gnl_strlen(buffer) - i + 1);
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		str[j++] = buffer[i++];
	free(buffer);
	str[j] = '\0';
	return (str);
}

char	*get_line(char *buffer)
{
	char	*line;
	int		i;
	int		line_width;

	if (!buffer[0])
		return (NULL);
	i = 0;
	line_width = line_len_n(buffer);
	line = malloc(sizeof(char *) * (line_width + 1));
	if (!line)
		return (NULL);
	while (i < line_width && buffer[i])
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = 0;
	return (line);
}

char	*get_buffer(int fd, char *buffer)
{
	int		nb;
	char	*b;

	nb = 1;
	b = malloc(sizeof(char *) * BUFFER_SIZE + 1);
	if (!b)
		return (free_buffer(b));
	while (nb > 0 && !gnl_strchr(buffer, '\n'))
	{
		nb = read(fd, b, BUFFER_SIZE);
		if (nb < 0)
			return (free_buffer(b));
		b[nb] = 0;
		buffer = gnl_strjoin(buffer, b);
	}
	free(b);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = get_buffer(fd, buffer);
	if (!buffer)
		return (free_buffer(buffer));
	line = get_line(buffer);
	buffer = set_buffer_pos(buffer);
	return (line);
}
