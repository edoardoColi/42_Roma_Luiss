/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:22:37 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:06:27 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"

int	redirector(t_command *com)
{
	char	*command;

	command = com->command;
	if (ft_strcmp(command, "unset"))
		return (unset(com));
	else if (ft_strcmp(command, "cd"))
		return (cd(com));
	else if (ft_strcmp(command, "echo"))
		return (echo(com));
	else if (ft_strcmp(command, "pwd"))
		return (pwd());
	else if (ft_strcmp(command, "env"))
		return (env(com));
	else if (ft_strcmp(command, "exit"))
		return (ms_exit(com));
	else if (ft_strcmp(command, "export"))
		return (ft_export(com->arguments, com->shell));
	return (-1);
}

int	is_builtin(t_command *com)
{
	char	*command;

	command = com->command;
	if (ft_strcmp(command, "unset"))
		return (0);
	else if (ft_strcmp(command, "cd"))
		return (0);
	else if (ft_strcmp(command, "echo"))
		return (0);
	else if (ft_strcmp(command, "pwd"))
		return (0);
	else if (ft_strcmp(command, "env"))
		return (0);
	else if (ft_strcmp(command, "exit"))
		return (0);
	else if (ft_strcmp(command, "export"))
		return (0);
	return (-1);
}
