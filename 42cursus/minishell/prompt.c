/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:17:55 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:06:27 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "glob.h"

static char	*remove_home(char *str, char *home)
{
	char	*new;
	int		i;
	int		j;

	new = ft_calloc(sizeof(char), ft_strlen(str) - ft_strlen(home) + 2);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == home[i])
			i++;
		else
			break ;
	}
	if (str[i])
		i++;
	while (str[i])
		new[j++] = str[i++];
	return (new);
}

static char	*our_prompt_2(t_hellmini *shell, char *buff)
{
	char	*user;

	buff[0] = '\0';
	buff = ft_strjoin_free(buff, CBYEL, 1, 0);
	user = exp_tkn("USER", shell->env);
	if (!user)
		user = ft_calloc(sizeof(char), 1);
	buff = ft_strjoin_free(buff, user, 1, 1);
	buff = ft_strjoin_free(buff, PROMPT, 1, 0);
	return (buff);
}

char	*our_prompt(t_hellmini *shell, char *str)
{
	char	*buff;
	char	*home_path;
	char	*new_path;

	home_path = exp_tkn("HOME", shell->env);
	if (!home_path)
		home_path = ft_calloc(sizeof(char), 1);
	buff = ft_calloc(sizeof(char), 2);
	buff = our_prompt_2(shell, buff);
	if (home_path[0] && !ft_strncmp(str, home_path, ft_strlen(home_path)))
	{
		buff = ft_strjoin_free(buff, "~/", 1, 0);
		new_path = remove_home(str, home_path);
		buff = ft_strjoin_free(buff, new_path, 1, 1);
		free(str);
	}
	else
		buff = ft_strjoin_free(buff, str, 1, 1);
	free(home_path);
	buff = ft_strjoin_free(buff, CWHITE"$ ", 1, 0);
	return (buff);
}
