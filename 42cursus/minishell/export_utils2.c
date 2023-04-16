/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:21:27 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:06:27 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"

int	ft_strchr_len(char *str, char c)
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

int	ft_strcmp_better(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}

void	print_env_vars(char *env_cpy)
{
	int		i;
	int		k;
	int		not_func;
	char	tmp[4095];

	i = -1;
	k = -1;
	not_func = 0;
	while (env_cpy[++i])
	{
		if (i > 0 && env_cpy[i - 1] == '=' && not_func++ >= 0)
			tmp[++k] = '"';
		else if (env_cpy[i] == '"')
			tmp[++k] = '\\';
		tmp[++k] = env_cpy[i];
	}
	if (tmp[k] == '=' && !env_cpy[i] && not_func++ >= 0)
		tmp[++k] = '"';
	if (not_func)
		tmp[++k] = '"';
	tmp[++k] = '\n';
	tmp[++k] = '\0';
	ft_putstr_fd(tmp, 1);
}
