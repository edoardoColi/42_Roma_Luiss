/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:19:52 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:29:42 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	until_space(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isnotspace(str[i]))
		i++;
	return (i);
}

int	to_next_quote(char *str, int i, char quote)
{
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}

int	i_after_quote(char *str, int i, int *iw, int *in)
{
	char	c;

	c = str[i];
	if (*iw == 0 && str[i + 1] && str[i] != str[i + 1])
	{
		*iw = 1;
		*in = *in + 1;
	}
	i++;
	i = to_next_quote(str, i, c);
	return (i);
}

static int	calc_redir(char *str, int *i, int *in_word)
{
	*in_word = 1;
	if (str[*i] == str[*i + 1])
		*i = *i + 1;
	return (1);
}

int	items_in_string(char *str)
{
	int	items_number;
	int	in_word;
	int	i;

	i = 0;
	in_word = 0;
	items_number = 0;
	while (str[i])
	{	
		if (ft_isquote(str[i]))
		{
			i = i_after_quote(str, i, &in_word, &items_number);
			if (!in_word && items_number++ >= 0)
				in_word = 1;
		}
		else if (ft_isredirection(str[i]) && calc_redir(str, &i, &in_word))
			items_number++;
		else if (ft_isnotspace(str[i]) && in_word == 0 && !in_word++)
			items_number++;
		else if (ft_isspace(str[i]) || (i && ft_isredirection(str[i - 1])))
			in_word = 0;
		i++;
	}
	return (items_number);
}
