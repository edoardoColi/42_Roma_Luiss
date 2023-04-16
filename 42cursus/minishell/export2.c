/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:21:34 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:06:27 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"

static int	ft_strlen_tochar(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c && str[i] != '\n')
		i++;
	return (i);
}

static char	**allocate_and_copy_env(char **env)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(sizeof(char *), ft_cmtxlen(env) + 2);
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i++])
		new_env[i - 1] = ft_strdup(env[i - 1]);
	return (new_env);
}

int	export_compare_values(char *entry, char *arg)
{
	if (ft_strlen_tochar(entry, '=') != ft_strlen_tochar(arg, '='))
		return (0);
	if (ft_strncmp(entry, arg, ft_strlen_tochar(arg, '=')))
		return (0);
	else
	{
		if (ft_strchr(arg, '='))
			return (1);
		else
			return (2);
	}
	return (0);
}

void	add_string_to_env(t_hellmini *shell, char *str, char **env)
{
	char	**new_env;
	int		exist;
	int		i;

	new_env = allocate_and_copy_env(env);
	if (!new_env)
		return ;
	i = 0;
	while (new_env[i])
	{
		exist = export_compare_values(new_env[i], str);
		if (exist == 1)
		{
			free(new_env[i]);
			new_env[i] = str;
		}
		if (exist)
			break ;
		i++;
	}
	if (i >= (int) ft_cmtxlen(new_env))
		new_env[i] = ft_strdup(str);
	ft_free_cmatrix(shell->env);
	shell->env = new_env;
}

char	**insert_values_env(char **args, char **env)
{
	int	exist;
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		if (export_check_argument(args[i]) && i++ >= 0)
			continue ;
		j = 0;
		while (env[j])
		{
			val_env_part_2(&exist, &env[j], args[i]);
			if (exist)
				break ;
			j++;
		}
		if (j >= (int) ft_cmtxlen(env))
			env[j] = ft_strdup(args[i]);
		i++;
	}
	return (env);
}
