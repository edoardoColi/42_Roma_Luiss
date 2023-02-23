/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:15:39 by ecoli             #+#    #+#             */
/*   Updated: 2023/02/24 00:13:37 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

/*
start: Start time
Return the time since the start in milliseconds.
Calculates the difference in milliseconds from
the starting time with the current time.
*/
long int	get_timestamp(struct timeval start)
{
	struct timeval	end;
	long int		millis_s;
	long int		millis_e;

	if (gettimeofday(&end, NULL) != 0)
	{
		ft_putstr_fd("Gettimeofday fail\n", err);
		return (-1);
	}
	else
	{
		millis_s = (start.tv_sec * 1000) + (start.tv_usec / 1000);		//Conversion to milliseconds from seconds and microseconds to milliseconds
		millis_e = (end.tv_sec * 1000) + (end.tv_usec / 1000);
	}
	if (millis_e - millis_s > 0)
		return (millis_e - millis_s);
	else
		return (-1);
}

/*
str: string
Return the integer.
Calculate the integer it refers
to from the source string.
*/
int	adhoc_atoi(const char *str)
{
	int					i;
	unsigned int		ret;

	i = 0;
	ret = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		ret = ret * 10 + (str[i] - 48);		//Subtracting the offset of 0, according to the asci table, we get the char as a number
		i++;
	}
	return (ret);
}

/*
My own function implementing the original one.
For more use "man isdigit"
*/
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/*
s: The string to output.
fd: The file descriptor on which to write.
Return none.
Outputs the string ’s’ to the given file
descriptor.
*/
void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
	}
}

/*
c: The character to output.
fd: The file descriptor on which to write.
Return none.
Outputs the character ’c’ to the given file
descriptor.
*/
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
