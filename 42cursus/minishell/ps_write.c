/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:19:58 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:29:41 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	write_word(char *cnt, t_command *cmd)
{
	int	i;
	int	t;
	int	c;

	i = 0;
	t = 0;
	c = 0;
	while (cmd->str[0])
	{
		if (ft_isquote(cmd->str[0]))
		{
			c = 0;
			t = to_next_quote(cmd->str, 1, cmd->str[0]);
			while (c++ <= t)
				cnt[i++] = cmd->str++[0];
		}
		else
			cnt[i++] = cmd->str++[0];
		if (ft_isspace(cmd->str[0]) || ft_isredirection(cmd->str[0])
			|| cmd->str[0] == '|')
			break ;
	}
	cnt[i] = '\0';
}

void	write_redirection(t_command *cmd, char c1, char c2)
{
	int	red_n;

	red_n = 0;
	while (cmd->red_type[red_n] && cmd->red_type[red_n] != -1)
		red_n++;
	if (c2 && c2 == '<')
		cmd->red_type[red_n] = HERDOC;
	else if (c2 && c2 == '>')
		cmd->red_type[red_n] = REDAPP;
	else if (c1 == '<')
		cmd->red_type[red_n] = REDIN;
	else if (c1 == '>')
		cmd->red_type[red_n] = REDOUT;
	ps_move_to_next_char(cmd);
	cmd->red[red_n] = ft_calloc(sizeof(char), ft_strlen(cmd->str) + 1);
	write_word(cmd->red[red_n], cmd);
}

void	fill_token(t_command *cmd, int *argc)
{
	cmd->tokens[*argc] = ft_calloc(sizeof(char), ft_strlen(cmd->str) + 1);
	if (!(cmd->tokens[*argc]))
		return ;
	write_word(cmd->tokens[*argc], cmd);
	if (cmd->tokens[*argc] != NULL && cmd->tokens[*argc][0] == '|')
		cmd->shell->mc_pipes += 1;
	*argc = *argc + 1;
}

void	before_write_word(t_command *cmd, int *argc, int *items)
{
	char	c;

	c = ft_isredirection(cmd->str[0]);
	if (c)
	{
		cmd->str++;
		if (ft_isredirection(cmd->str[0]) == c)
		{
			cmd->str++;
			write_redirection(cmd, c, c);
		}
		else
			write_redirection(cmd, c, 0);
		*items = *items - 2;
	}
	else
		fill_token(cmd, argc);
	ps_move_to_next_char(cmd);
}
