/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:01:02 by ecoli             #+#    #+#             */
/*   Updated: 2022/03/25 17:24:04 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
fd: The file descriptor to read from.
Return the read line: correct behavior 
NULL: there is nothing else to read, or an error 
occurred.
A function that returns a line read from a 
file descriptor.
*/
char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];	//Automatically initialized empty because declared static
	char		*line;					//Return value

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (check_line(buffer))
		line = get_line_from_buf(buffer);
	else
		line = get_line_from_fd(fd, buffer);
	return (line);
}

/*
fd: The file descriptor to read from.
buffer: The buffer where to put what you read from the file.
Return the read line: correct behavior 
NULL: there is nothing else to read, or an error 
occurred.
A function that returns a line read from a 
file descriptor and update the buffer for later use.
*/
char	*get_line_from_fd(int fd, char buffer[])
{
	ssize_t	n;
	int		flag;
	char	*str;								//Return value

	str = NULL;
	if (attach_buffer(&str, &buffer) == -1)		//In case there was something from before
	{											//-1 value is malloc() fail
		free (str);
		return (NULL);
	}
	n = read(fd, buffer, BUFFER_SIZE);
	while (n > 0)
	{
		flag = attach_buffer(&str, &buffer);
		if (flag == -1)							//-1 value is malloc() fail
		{
			free (str);
			return (NULL);
		}
		if (flag)
			return (str);
		n = read(fd, buffer, BUFFER_SIZE);
	}
	if (str_len(str) > 0)
		return (str);
	free (str);
	return (NULL);
}

/*
buffer: The buffer from where read the next line.
Return the read line: correct behavior 
NULL: there is nothing else to read, or an error 
occurred.
A function that returns a line read from  
the buffer that already contains a new line 
without having to read from fd, also update 
the buffer for later use.
*/
char	*get_line_from_buf(char buffer[])
{
	int		flag;
	char	*str;							//Return value

	str = NULL;
	flag = attach_buffer(&str, &buffer);
	if (flag == -1)							//-1 value is malloc() fail
	{
		free (str);
		return (NULL);
	}
	return (str);
}

/*
str: The string to check.
Return 1 if contains a newline 
0 otherwise.
Check that there is at least one '\n'.
*/
int	check_line(char str[])
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '\n')
				return (1);
			i++;
		}
	}
	return (0);
}
