/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:20:46 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:29:44 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	lx_error(unsigned char chr)
{
	if (ft_isquote(chr))
		ft_printf("minishell: expected `%c' found `newline' instead\n", chr);
	else if (chr == '\n')
		ft_printf("minishell: syntax error near unexpected token `newline'\n");
	else if (chr == '\0')
		ft_printf("minishell: syntax error near unexpected token `EOF'\n");
	else
		ft_printf("minishell: syntax error near unexpected token `%c'\n", chr);
	return (157);
}

static void	move_to_end_quote(char **line)
{
	char	quote;

	quote = (*line)[0];
	if (ft_isquote(quote))
	{
		(*line)++;
		while ((*line)[0] != quote)
			(*line)++;
		(*line)++;
	}
	if (ft_isquote(*line[0]))
		move_to_end_quote(line);
}

void	move_to_next_char(char **line)
{
	while (ft_isspace(*line[0]))
		(*line)++;
}

int	syntax_check_2(char *line)
{
	unsigned char	cc;

	move_to_next_char(&line);
	if (line[0] == '|')
		return (lx_error(line[0]));
	cc = line[0];
	while (line[0] && line[0] != '\n')
	{
		move_to_end_quote(&line);
		if (!line[0])
			break ;
		if ((ft_isredirection(cc) && line[0] == '|')
			|| (cc == '|' && line[0] == '|'))
			return (lx_error(line[0]));
		cc = line[0];
		if (cc && ft_strchr(UNEXPECTED, cc))
			return (lx_error(cc));
		if (ft_isredirection(cc) && ft_isredirection(line[1]) && cc != line[1])
			return (lx_error(line[1]));
		line++;
		move_to_next_char(&line);
	}
	if (ft_isredirection(cc) && (!line[0] || line[0] == '\n'))
		return (lx_error('\n'));
	return (0);
}

int	check_syntax(char *line, int i)
{
	char	ch;

	ch = check_closures(line, i);
	if (ch)
		return (lx_error(ch));
	while (line[i] != 0)
	{
		if (ms_isoperator(line[i]) == 1)
		{
			if (check_operator(line, i) == -1)
				return (lx_error(line[i]));
		}
		i++;
	}
	return (syntax_check_2(line));
}
