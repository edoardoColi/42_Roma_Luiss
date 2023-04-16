/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:21:37 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:06:27 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"

static int	stamp_error(char *str)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("': not a valild identifier\n", STDERR_FILENO);
	return (1);
}

int	export_check_argument(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '=')
		return (stamp_error("="));
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		else
			return (stamp_error(str));
	}
	return (0);
}

void	val_env_part_2(int *exist, char **str, char *arg)
{
	*exist = export_compare_values(*str, arg);
	if (*exist == 1)
	{
		free(*str);
		(*str) = ft_strdup(arg);
	}
}
