/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli    <ecoli   @student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:42:43 by ecoli             #+#    #+#             */
/*   Updated: 2023/03/23 10:46:52 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

static int	ft_strchr_len(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	if (i >= (int) ft_strlen(str))
		return (-1);
	return (i);
}

int	env(t_command *cmd)
{
	int		i;

	i = 0;
	while (cmd->shell->env[i])
	{
		if (!(ft_strchr_len(cmd->shell->env[i], '=') == -1))
			ft_putendl_fd(cmd->shell->env[i], 1);
		i++;
	}
	return (0);
}
