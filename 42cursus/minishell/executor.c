/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:55:29 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:06:27 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "glob.h"

static void	set_signals(void)
{
	signal(SIGINT, control_c_signal);
	signal(SIGQUIT, control_c_signal);
}

void	ft_execv(t_command *cmd, int *status)
{
	char	*path;
	int		ecode;

	if (cmd->command)
		ecode = redirector(cmd);
	if (cmd->command && ecode != -1)
	{
		set_ecode(ecode);
		return ;
	}
	if (cmd->command && ft_strchr(cmd->command, '/'))
		path = ft_strdup(cmd->command);
	else if (cmd->command)
		path = ft_findpath(cmd, 0);
	else
		return ;
	if (!fork())
		execute_process(cmd->shell, path, cmd->arguments);
	set_ecode(0);
	set_signals();
	waitpid(0, status, 0);
	if (*status && get_ecode() != 130
		&& get_ecode() != 131 && WIFEXITED(*status))
		set_ecode(WEXITSTATUS(*status));
	ft_free_ptr(path);
}

int	shift_arguments(t_command *cmd, int i)
{
	while (i < cmd->args_number)
	{
		if (cmd->arguments[i] && !cmd->arguments[i][0]
				&& cmd->arguments[i + 1] && cmd->arguments[i + 1][0])
		{
			cmd->arguments[i] = cmd->arguments[i + 1];
			cmd->arguments[i + 1] = NULL;
			shift_arguments(cmd, 0);
		}
		i++;
	}
	if (!cmd->arguments || !cmd->arguments[0] || (!cmd->arguments[0][0]))
		return (1);
	free(cmd->command);
	cmd->command = ft_strdup(cmd->arguments[0]);
	return (0);
}

static int	command_not_found(t_command *cmd, int std_cpy[2])
{
	char	*path;

	if (cmd->command && ft_strchr(cmd->command, '/'))
		path = ft_strdup(cmd->command);
	else if (cmd->command)
		path = ft_findpath(cmd, 0);
	else
		path = NULL;
	if (!path)
	{
		close(std_cpy[0]);
		close(std_cpy[1]);
		set_ecode(127);
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->command, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		return (1);
	}
	ft_free_ptr(path);
	return (0);
}

void	ft_executor(t_command *cmd)
{
	int		std_cpy[2];

	std_cpy[0] = dup(STDIN_FILENO);
	std_cpy[1] = dup(STDOUT_FILENO);
	if (cmd->spc[PIPE])
		ft_pipe(cmd, std_cpy, 118, -1);
	else if (cmd)
	{
		if (cmd->spc[DQUOTE] || cmd->spc[SQUOTE] || cmd->spc[MQUOTE]
			|| cmd->spc[CASH] || cmd->spc[TILDE])
			expander(cmd);
		if (cmd->command && cmd->command[0] == '\0' && shift_arguments(cmd, 0))
			return ;
		if (cmd->command && is_builtin(cmd) == -1
			&& command_not_found(cmd, std_cpy))
			return ;
		if (!cmd->spc[PIPE] && (cmd->spc[REDIN] || cmd->spc[REDOUT]
				|| cmd->spc[REDAPP] || cmd->spc[HERDOC]))
		{
			exec_redir(cmd, &std_cpy[0], &std_cpy[1]);
			return ;
		}
		ft_execv(cmd, &(cmd->shell->exit_status));
	}
}
