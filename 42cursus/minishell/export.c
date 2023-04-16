/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:21:31 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:29:45 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"

int	alpha_cmp(char **str1, char **str2)
{
	char	*tmp;

	tmp = *str1;
	*str1 = *str2;
	*str2 = tmp;
	return (0);
}

void	alpha_sort(char **mtrx)
{
	int	i;
	int	n;
	int	k;

	k = 0;
	n = 0;
	while (mtrx[n])
		n++;
	while (k < n)
	{
		i = 0;
		while (i < n - 1 - k)
		{
			if (ft_strcmp_better(mtrx[i], mtrx[i + 1]) > 0)
				alpha_cmp(&mtrx[i], &mtrx[i + 1]);
			i++;
		}
		k++;
	}
}

char	**export_aux(char **key_value, char **env_cpy)
{
	int		i;
	int		k;
	char	**big_buff;

	k = 0;
	i = 1;
	while (key_value[i++])
		;
	while (env_cpy[k++])
		;
	big_buff = ft_calloc(sizeof(char *), i + k + 1);
	k = 0;
	while (env_cpy[k++])
		big_buff[k - 1] = ft_strdup(env_cpy[k - 1]);
	big_buff = insert_values_env(key_value, big_buff);
	env_cpy = big_buff;
	return (env_cpy);
}

int	ft_export(char **key_value, t_hellmini *shell)
{
	char	**env_cpy;
	int		i;

	if (key_value && key_value[1])
		env_cpy = export_aux(key_value, shell->env);
	else
	{
		env_cpy = ft_arrdup(shell->env);
		alpha_sort(env_cpy);
		if (key_value[1] == NULL)
		{
			i = -1;
			while (env_cpy[++i])
			{
				write(1, "declare -x ", 11);
				print_env_vars(env_cpy[i]);
			}
		}
	}
	ft_free_cmatrix(shell->env);
	shell->env = env_cpy;
	return (0);
}
