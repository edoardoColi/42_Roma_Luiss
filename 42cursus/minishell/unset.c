/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:22:34 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:06:27 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"

static char	**envcpy_len(int len)
{
	char	**new_env;

	new_env = ft_calloc(sizeof(char *), len + 1);
	if (!new_env)
		return (NULL);
	return (new_env);
}

static char	*envcpy_line(char *line)
{
	char	*new_line;
	int		i;

	i = 0;
	while (line[i] != 0)
		i++;
	new_line = ft_calloc(sizeof(char), i + 1);
	if (!(new_line))
		return (NULL);
	i = 0;
	while (line[i] != 0)
	{
		(new_line)[i] = line[i];
		i++;
	}
	return (new_line);
}

static int	cmp_arguments(char *env_string, char **args)
{
	int		i;

	i = 1;
	while (args[i])
	{
		if (!ft_strncmp(args[i], env_string, ft_strlen(args[i])))
			return (1);
		i++;
	}
	return (0);
}

int	unset(t_command *com)
{
	char	**new_env;
	int		lenght;
	int		i;
	int		j;

	i = 0;
	j = 0;
	lenght = ft_cmtxlen(com->shell->env);
	if (ft_cmtxlen(com->arguments) == 1)
		return (0);
	new_env = envcpy_len(lenght);
	if (ft_cmtxlen(com->arguments) > 1)
	{
		while (lenght > i)
		{
			if (!cmp_arguments(com->shell->env[i], com->arguments))
				new_env[j++] = envcpy_line(com->shell->env[i]);
			i++;
		}
	}
	ft_free_cmatrix(com->shell->env);
	com->shell->env = new_env;
	return (0);
}
