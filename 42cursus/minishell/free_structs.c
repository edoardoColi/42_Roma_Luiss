/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:17:14 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:06:27 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"

static void	free_things_inside_command(t_command *cmd)
{
	ft_free_cmatrix(cmd->arguments);
	ft_free_cmatrix(cmd->tokens);
	ft_free_ptr(cmd->red_type);
	ft_free_ptr(cmd->command);
	ft_free_cmatrix(cmd->red);
	ft_free_ptr(cmd->str);
	ft_free_ptr(cmd);
}

void	free_commands(t_hellmini *shell)
{
	t_command	*cmd;
	t_command	*nxt;

	cmd = shell->current_cmd;
	nxt = NULL;
	while (cmd)
	{
		nxt = cmd->next;
		free_things_inside_command(cmd);
		cmd = nxt;
	}
	shell->current_cmd = NULL;
}

void	free_shell(t_hellmini *shell)
{
	if (shell->input)
		free(shell->input);
	ft_free_cmatrix(shell->env);
	free_commands(shell);
	free(shell);
}
