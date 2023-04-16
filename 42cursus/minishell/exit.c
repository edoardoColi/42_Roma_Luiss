/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli    <ecoli   @student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:22:43 by ecoli             #+#    #+#             */
/*   Updated: 2023/03/23 10:46:52 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"

int	check_exit_argument(char *com)
{
	unsigned int	i;

	i = 0;
	if (com[0] == '-' || com[0] == '+')
		i = 1;
	if (ft_strlen(com) - i > 19)
		return (-1);
	while (ft_isdigit(com[i++]))
	{
		if (!com[i])
			return (0);
	}
	return (-1);
}

int	exit_check_spaces(const char *s)
{
	int	i;

	i = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == ' ')
		i++;
	return (i);
}

long long	ft_atoll(const char *str)
{
	long	i;
	long	sign;
	long	res;

	i = exit_check_spaces(str);
	sign = 1;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-' )
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

void	exit_without_arguments(t_hellmini *shell, int ret)
{
	if (ret > 1)
		return ;
	free_shell(shell);
	exit(0);
}

int	ms_exit(t_command *cmd)
{
	int	ret;

	ret = 0;
	while (cmd->arguments[ret])
		ret++;
	ft_printf("exit\n");
	exit_without_arguments(cmd->shell, ret);
	if (check_exit_argument(cmd->arguments[1]) != 0)
	{
		ft_printf("minishell: exit: %s: numeric argument required\n",
			cmd->arguments[1]);
		ret = 255;
	}
	else if (ret > 2)
	{
		ft_printf("minishell: exit: too many arguments\n");
		return (1);
	}
	else if (ret == 2)
	{
		ret = ft_atoll(cmd->arguments[1]);
		ret %= 256 + 256 * (ret < 0);
	}
	free_shell(cmd->shell);
	exit(ret);
}
