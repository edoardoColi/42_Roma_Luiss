/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:22:51 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:24:03 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"

static void	write_old_path_in_env(t_command *cmd, char *path)
{
	char	*cpath;

	cpath = getcwd(NULL, 0);
	if (ft_strcmp(path, cpath))
	{
		ft_free_ptr(cpath);
		ft_free_ptr(path);
		return ;
	}
	ft_free_ptr(cpath);
	add_string_to_env(cmd->shell,
		ft_strjoin_free("OLDPWD=", path, 0, 1), cmd->shell->env);
}

static int	cd_prev_folder(t_command *cmd, char *arg, int *pfc)
{
	char	*old_path;

	old_path = exp_tkn("OLDPWD", cmd->shell->env);
	if (arg[0] == '-' && arg[1] == '\0')
	{
		if (old_path == NULL && (*pfc)-- >= 0)
			ft_printf("minishell: cd: OLDPWD not set\n");
		else
		{
			write_old_path_in_env(cmd, getcwd(NULL, 0));
			if (chdir(old_path) && (*pfc)-- >= 0)
			{
				ft_printf("minishell: cd: %s: Not a directory\n", old_path);
				ft_free_ptr(old_path);
				return (1);
			}
			ft_printf("%s\n", old_path);
			*pfc = 1;
			ft_free_ptr(old_path);
		}
		return (1);
	}
	*pfc = 0;
	ft_free_ptr(old_path);
	return (0);
}

static int	cd_execute(t_command *cmd, int pfc, int error)
{
	char	*old_path;

	old_path = getcwd(NULL, 0);
	if (cd_prev_folder(cmd, cmd->arguments[1], &pfc) == 1)
	{
		if (pfc == -1)
		{
			free(old_path);
			return (1);
		}
		error = 0;
	}
	else
		error = chdir(cmd->arguments[1]);
	if (error)
	{
		set_ecode(1);
		free(old_path);
		ft_printf("minishell: cd: %s: Not a directory\n", cmd->arguments[1]);
		return (1);
	}
	write_old_path_in_env(cmd, old_path);
	return (0);
}

static void	cd_replace_null(t_command *cmd, char *str)
{
	int		i;

	ft_free_cmatrix(cmd->arguments);
	cmd->arguments = ft_calloc(sizeof(char *), 3);
	cmd->arguments[0] = ft_strdup(cmd->command);
	cmd->arguments[1] = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	i = 0;
	while (str[i])
	{
		cmd->arguments[1][i] = str[i];
		i++;
	}
	cmd->arguments[2] = NULL;
}

int	cd(t_command *cmd)
{
	char	*home;

	home = exp_tkn("HOME", cmd->shell->env);
	if (cmd->arguments[1] && cmd->arguments[2])
	{
		ft_printf("minishell: cd: too many arguments\n");
		return (1);
	}
	else if (!(cmd->arguments[1]))
		cd_replace_null(cmd, home);
	ft_free_ptr(home);
	return (cd_execute(cmd, 0, -1));
}
