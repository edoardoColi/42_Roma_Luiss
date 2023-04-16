/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:19:26 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:29:43 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	set_command_name(t_command *cmd)
{
	int	i;

	i = 0;
	if (!(cmd->arguments && cmd->arguments[0]))
	{
		cmd->spc[NOCMD] = 1;
		return ;
	}
	cmd->command = ft_calloc(sizeof(char), ft_strlen(cmd->arguments[0]) + 1);
	while (cmd->arguments[0][i++])
		cmd->command[i - 1] = cmd->arguments[0][i - 1];
	cmd->command[i - 1] = '\0';
}

static void	set_arguments(t_command *cmd, int args, int i)
{
	int	j;

	cmd->arguments = (char **) malloc(sizeof(char *) * (args + 1));
	if (!(cmd->arguments))
		return ;
	i = 0;
	while (i < args)
	{
		if (cmd->tokens[i] != NULL && 0[cmd->tokens[i]] == '|')
			break ;
		cmd->arguments[i] = ft_calloc(sizeof(char),
				ft_strlen(cmd->tokens[i]) + 1);
		if (!cmd->arguments[i])
			return (free(cmd->arguments));
		j = 0;
		while (cmd->tokens[i][j++])
			cmd->arguments[i][j - 1] = cmd->tokens[i][j - 1];
		i++;
	}
	cmd->arguments[i] = NULL;
	if (i == 0)
		cmd->arguments[0] = NULL;
}

static void	set_cmd_flags(t_command *cmd, int i)
{
	char	quote;
	int		q;

	q = 0;
	quote = 0;
	while (cmd->str[i])
	{
		set_meta_flags(cmd, cmd->str[i]);
		if (ft_isquote(cmd->str[i]) && q == 0)
		{
			quote = cmd->str[i];
			q = 1;
		}
		else if (q == 1 && ft_isquote(cmd->str[i]) == quote)
		{
			quote = 0;
			q = 0;
		}
		if (q == 0)
			set_operator_flags(cmd, cmd->str, &i);
		i++;
	}
}

static int	ps_split_string(t_command *cmd)
{
	char	*init;
	int		items;
	int		red_n;
	int		c;

	init = cmd->str;
	ps_move_to_next_char(cmd);
	red_n = red_in_string(cmd, cmd->str, 0);
	if (red_n > 0)
		ft_filliarrayto_n(cmd->red_type, EMPTY, red_n);
	items = items_in_string(cmd->str);
	cmd->tokens = NULL;
	cmd->tokens = ft_calloc(sizeof(char *), items + 1);
	if (!(cmd->tokens))
		return (0);
	c = 0;
	while (cmd->str[0] != 0)
		before_write_word(cmd, &c, &items);
	cmd->tokens[c] = NULL;
	cmd->str = init;
	return (items);
}

int	parser(t_hellmini *sh)
{
	t_command	*cmd;
	int			args;

	sh->mc_pipes = 0;
	cmd = sh->current_cmd;
	while (cmd && cmd != NULL)
	{
		args = ps_split_string(cmd);
		set_cmd_flags(cmd, 0);
		set_arguments(cmd, args, 1);
		set_command_name(cmd);
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
	return (SUCCESS);
}
