/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_flags_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:19:41 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:29:42 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	exit_quotes_if_it_is_one(char *str, int i)
{
	char	c;

	c = ft_isquote(str[i]);
	if (!c)
		return (i);
	i++;
	while (!(ft_isquote(str[i]) == c))
		i++;
	return (i);
}

int	red_in_string(t_command *cmd, char *str, int red_n)
{
	char	c;
	int		i;

	i = 0;
	c = 0;
	while (str[i])
	{
		i = exit_quotes_if_it_is_one(str, i);
		c = ft_isredirection(str[i]);
		if (c && str[i + 1] && ft_isredirection(str[i + 1]) && red_n++ >= 0)
			i += 2;
		else if (c && red_n++ >= 0)
			i += 1;
		else
			i += 1;
	}
	if (red_n > 0)
	{
		cmd->red_type = ft_calloc(sizeof(int), red_n + 1);
		cmd->red = ft_calloc(sizeof(char *), red_n + 1);
	}
	return (red_n);
}

void	set_operator_flags(t_command *cmd, char *s, int *m)
{
	if (s[*m] == '|')
		cmd->spc[PIPE] = 1;
	else if (s[*m] == '>' && s[*m + 1] && s[*m + 1] == '>')
	{
		cmd->spc[REDAPP] = 1;
		*m = *m + 1;
	}
	else if (s[*m] == '<' && s[*m + 1] && s[*m + 1] == '<')
	{
		cmd->spc[HERDOC] = 1;
		*m = *m + 1;
	}
	else if (s[*m] == '<')
		cmd->spc[REDIN] = 1;
	else if (s[*m] == '>')
		cmd->spc[REDOUT] = 1;
	else if (s[*m] == '~')
		cmd->spc[TILDE] = 1;
}

void	set_meta_flags(t_command *cmd, char c)
{
	if (c == '$')
		cmd->spc[CASH] = 1;
	else if (c == '\'' && cmd->spc[DQUOTE] == 1)
		cmd->spc[MQUOTE] = 1;
	else if (c == '"' && cmd->spc[SQUOTE] == 1)
		cmd->spc[MQUOTE] = 1;
	else if (c == '\'')
		cmd->spc[SQUOTE] = 1;
	else if (c == '"')
		cmd->spc[DQUOTE] = 1;
}
