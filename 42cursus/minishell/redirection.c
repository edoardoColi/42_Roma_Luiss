/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:15:03 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:25:03 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

static int	last_redir(t_command *cmd, int type)
{
	int	pos;
	int	n;

	pos = -1;
	n = -1;
	while (++n < (int) ft_arrlen(cmd->red_type))
	{
		if (!type
			&& (cmd->red_type[n] == REDIN || cmd->red_type[n] == HERDOC))
			pos = n;
		else if (type
			&& (cmd->red_type[n] == REDOUT || cmd->red_type[n] == REDAPP))
			pos = n;
	}
	return (pos);
}

void	stamp_no_file_error(char *file)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}

static void	cycle_redirections(t_command *cmd, int *stdin, int *stdout)
{
	t_redir	red;

	red.n = 0;
	red.lin = last_redir(cmd, 0);
	red.lout = last_redir(cmd, 1);
	while (red.n < (int) ft_arrlen(cmd->red_type))
	{
		if (cmd->red_type[red.n] == REDIN)
			red_in(cmd, red, stdin);
		else if (cmd->red_type[red.n] == HERDOC)
			red_here_doc(cmd, red, stdin);
		red.n += 1;
	}
	red.n = 0;
	while (red.n < (int) ft_arrlen(cmd->red_type))
	{
		if (cmd->red_type[red.n] == REDOUT)
			red_out(cmd, red, stdin, stdout);
		else if (cmd->red_type[red.n] == REDAPP)
			red_append(cmd, red, stdin, stdout);
		red.n = red.n + 1;
	}
}

void	exec_redir(t_command *cmd, int *stdin, int *stdout)
{
	cycle_redirections(cmd, stdin, stdout);
	if (cmd->red_error == -1)
		ft_execv(cmd, &cmd->shell->exit_status);
	else
		stamp_no_file_error(cmd->red[cmd->red_error]);
	if (last_redir(cmd, 1) > -1)
		dup2(*stdout, STDOUT_FILENO);
	dup2(*stdin, STDIN_FILENO);
	close(*stdin);
	close(*stdout);
}

void	exec_redir_pipe(t_command *cmd, int *stdin, int *stdout)
{
	cycle_redirections(cmd, stdin, stdout);
	if (cmd->red_error != -1)
		stamp_no_file_error(cmd->red[cmd->red_error]);
}
