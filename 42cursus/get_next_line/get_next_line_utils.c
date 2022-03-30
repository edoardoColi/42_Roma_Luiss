/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:03:52 by ecoli             #+#    #+#             */
/*   Updated: 2022/03/25 17:23:07 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
str: The reference to the external string that wanna fill.
buffer: The reference to the array where store the read data.
Returns -1 if malloc fails, 1 if the string is a complete 
line, 0 if you need to keep reading from file to complete it.
*/
int	attach_buffer(char **str, char *buffer[])
{
	int		len_str;
	int		len_buf;
	char	*new_str;
	int		i;

	i = 0;
	len_str = str_len(*str);
	len_buf = buf_nl_len(*buffer);
	new_str = malloc(sizeof(char) * (len_str + len_buf + 1));
	if (!new_str)
		return (-1);
	new_str[len_str + len_buf] = '\0';
	while (*str && (str[0])[i])			//Copy of the previous string
	{
		new_str[i] = (str[0])[i];
		i++;
	}
	free(*str);							//The memory of the string was allocated out of here
	while (i < len_str + len_buf)		//Copy of the array on the string
	{
		new_str[i] = (buffer[0])[i - len_str];
		i++;
	}
	*str = new_str;						//Replace the deleted string
	l_shift_buf(*buffer, len_buf);
	if (len_buf < BUFFER_SIZE || (str[0])[len_str + len_buf - 1] == '\n')
		return (1);
	else
		return (0);
}

/*
buffer: The buffer to read from.
n: How much to shift the buffer to the left.
Shifts the buffer to the left by n positions 
and fills the emptied with '\ 0'.
*/
void	l_shift_buf(char buffer[], int n)
{
	int		i;
	int		l;

	if (n == 0)
		return ;
	l = buf_len(buffer);
	if (n == l)								//In this case replaces everything written in the buffer
	{
		while (n)
		{
			buffer[n - 1] = '\0';
			n--;
		}
		return ;
	}
	i = 0;
	while (i < l)							//In this case replaces only the first part of the buffer
	{
		if (i + n < BUFFER_SIZE)
			buffer[i] = buffer[i + n];		//Characters to move
		else
			buffer[i] = '\0';				//Characters to clean up
		i++;
	}
}

/*
buf: The array to check.
Return the number of characters in the array, 
if finds '\n' counts and stops.
*/
int	buf_nl_len(char buf[])
{
	int	i;

	if (!buf[0])
		return (0);
	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (i + 1);			//Must also include '\n' just read
		i++;
	}
	return (i);
}

/*
buf: The array to check.
Return the number of characters up to '\0'.
*/
int	buf_len(char buf[])
{
	int	i;

	i = 0;
	while (buf[i])
		i++;
	return (i);
}

/*
s: the string to check up to '\0'.
Return the length of the string.
*/
int	str_len(char *s)
{
	int	l;

	l = 0;
	while (s && s[l] != '\0')
		l++;
	return (l);
}
