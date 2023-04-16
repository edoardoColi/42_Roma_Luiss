/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirpipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:55:52 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:29:40 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#define HEREDOC_MSG	"\033[1;97m> \033[0m"

void	ft_chooseredir(t_command *cmd, int *stdin_cpy, int *stdout_cpy)
{
	if (cmd->red_type[0] == HERDOC)
		ft_heredoc(cmd, stdin_cpy);
	else if (cmd->red_type[0] == REDIN)
		ft_redin(cmd, stdin_cpy);
	else if (cmd->red_type[0] == REDOUT)
		ft_redout(cmd, stdin_cpy, stdout_cpy);
	else if (cmd->red_type[0] == REDAPP)
		ft_redappend(cmd, stdout_cpy);
}
