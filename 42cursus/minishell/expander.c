/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:21:18 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:07:09 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void	expand_dollar(t_hellmini *s, char buff[4095], char *(*str), int *i)
{
	char	*var_name;
	char	*var_val;
	int		c;

	if (expand_question(buff, str, i) == TRUE)
		return ;
	var_name = get_string_to_expand(str);
	if (!var_name)
		return ;
	var_val = exp_tkn(var_name, s->env);
	free(var_name);
	if (!var_val)
		return ;
	c = 0;
	while (var_val[c])
	{
		buff[*i] = var_val[c++];
		*i = *i + 1;
	}
	free(var_val);
}

static void	expand_double_quotes(t_hellmini *sh, char buff[4095],
char *(*str), int *i)
{
	if (*str[0] == '"')
	{
		(*str)++;
		while (*str[0] && *str[0] != '"')
		{
			if (*str[0] == '$')
				expand_dollar(sh, buff, str, i);
			else
			{
				buff[*i] = (*str)++[0];
				*i = *i + 1;
			}
		}
		(*str)++;
	}
}

static char	*get_and_allocate_new_string(char buff[4095])
{
	char	*str;
	int		i;

	str = ft_calloc(sizeof(char), ft_strlen(buff) + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (buff[++i])
		str[i] = buff[i];
	return (str);
}

static char	*replace_token(t_command *cmd, char *(*str))
{
	char	buff[4095];
	int		i;

	i = 0;
	expand_tilde(cmd->shell, buff, str, &i);
	while (*str[0])
	{
		to_next_single_quote(str, buff, &i);
		if (*str[0] == '\0')
			break ;
		if (*str[0] == '$')
			expand_dollar(cmd->shell, buff, str, &i);
		else if (*str[0] == '"')
			expand_double_quotes(cmd->shell, buff, str, &i);
		else
		{
			buff[i++] = *str[0];
			(*str)++;
		}
	}
	buff[i] = '\0';
	(*str) = get_and_allocate_new_string(buff);
	return (*str);
}

void	expander(t_command *cmd)
{
	char	*tmp;
	int		i;

	tmp = cmd->command;
	cmd->command = replace_token(cmd, &(cmd->command));
	free(tmp);
	i = 0;
	while (cmd->arguments && cmd->arguments[i] && cmd->arguments[i][0])
	{
		tmp = cmd->arguments[i];
		cmd->arguments[i] = replace_token(cmd, &(cmd->arguments[i]));
		free(tmp);
		i++;
	}
	cmd->args_number = i;
	i = 0;
	while (cmd->red && cmd->red[i] && cmd->red[i][0])
	{
		tmp = cmd->red[i];
		cmd->red[i] = replace_token(cmd, &(cmd->red[i]));
		free(tmp);
		i++;
	}
}
