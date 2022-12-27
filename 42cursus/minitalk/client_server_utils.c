/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_server_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:15:39 by ecoli             #+#    #+#             */
/*   Updated: 2022/12/27 16:14:04 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

/*
My own function implementing the original one.
For more use "man strlen" 
*/
size_t	ft_strlen(const char *s)
{
	size_t	l;

	l = 0;
	while (s[l] != '\0')
		l++;
	return (l);
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

/*
n: The integer to output.
fd: The file descriptor on which to write.
Return none.
Outputs the integer ’n’ to the given file
descriptor.
*/
void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n > 9)
	{
		ft_putnbr_fd((n / 10), fd);
		ft_putchar_fd(((n % 10) + '0'), fd);
	}
	else
		ft_putchar_fd((n + '0'), fd);
}

/*
My own function implementing the original one.
For more use "man memset" 
*/
void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = c;
		i++;
	}
	return (b);
}

/*
My own function implementing the original one.
For more use "man _atoi" 
*/
int	ft_atoi(const char *str)
{
	int					i;
	int					s;
	unsigned int		ret;

	s = 1;
	i = 0;
	ret = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')	//Are the various types of spaces
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		ret = ret * 10 + (str[i] - 48);							//Subtracting the offset of 0, according to the asci table, we get the char as a number
		i++;
	}
	return (s * ret);
}

/*
My own function implementing the original one.
For more use "man isdigit" 
*/
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
