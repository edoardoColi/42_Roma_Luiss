/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 04:14:26 by eddy              #+#    #+#             */
/*   Updated: 2023/02/23 15:13:48 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

/*
My own function implementing the original one.
For more use "man strncmp" 
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && (i < n - 1))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*
My own function implementing the string to double conversion, maneging dots.
*/
double	atod(const char *str)
{
	int		i;
	int		s;
	double	ret;
	double	power;

	s = 1;
	i = 0;
	ret = 0.0;
	power = 1.0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		ret = ret * 10 + (str[i] - 48);//Subtracting the offset of 0, according to the asci table, we get the char as a number
		i++;
	}
	if (str[i] == '\0')
		return (s * ret / power);
	if (str[i] != '.')
		return (0);
	else
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		ret = ret * 10 + (str[i] - 48);//Subtracting the offset of 0, according to the asci table, we get the char as a number
		power *= 10;
		i++;
	}
	return (s * ret / power);
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
