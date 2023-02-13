/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by eddy              #+#    #+#             */
/*   Updated: 2023/02/13 20:29:37 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

/*
*/
int		parser(char *cmds, int *n_cmds, char *envp[])
{
	int			i;
	char		*path;
	t_command	**command;

	printf("parso: %s\n",cmds);

	command = malloc(sizeof(t_command *) * (*n_cmds));
	if (!command)
	{
		printf("Malloc fail\n");
		exit(1);
	}
	i = -1;
	while (++i < *n_cmds)
	{
		command[i] = fill_cmd(i, cmds, envp);
	}
	printf("%s\n",command[0]->args[0]);
	printf("%s\n",command[1]->args[0]);
//	printf("%s , %s , %s\n",command[0]->args[2]);
//	exec_cmd();
	i = -1;
	while (++i < *n_cmds)
		free(command[i]);//devo liberare anche le cose dentro a command[i]
	free(command);
	return (0);
}

/*
*/
t_command	*fill_cmd(int n_cmds, char *in_line, char *envp[])
{
	int			i;
	int			j;
	int			tmp;
	int			arg;
	int			quote_rep;
	int			quotes_rep;
	char		cmd[2048];
	t_command	*ret_cmd;
	
	ret_cmd = malloc(sizeof(t_command) * 1);
	if (!ret_cmd)
	{
		printf("Malloc fail\n");
		exit(1);
	}
	tmp = -1;
	quote_rep = 0;
	quotes_rep = 0;
	i = 0;
	j = 0;
	while (in_line[i] != '\0')
	{
		if (in_line[i] == '\'' && quotes_rep % 2 == 0)
			quote_rep++;
		if (in_line[i] == '"' && quote_rep % 2 == 0)
			quotes_rep++;
		if (tmp == n_cmds - 1)
		{
			cmd[j] = in_line[i];
			j++;
		}
		if (in_line[i] == '|' && quote_rep % 2 == 0 && quotes_rep % 2 == 0)
			tmp++;
		if (tmp == n_cmds)
			break ;
		i++;
	}
	cmd[j] = '\0';
	trimmer(cmd);//dentro command ho il comando numero i del loop che chiama la funzione

printf("%sFINE\n",cmd);

	i = 0;
	j = 0;
	tmp = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ')
		{
			ret_cmd->args[tmp][j] = '\0';
			tmp++;
			j = 0;
		}
		else
		{
			ret_cmd->args[tmp][j] = cmd[i];
			j++;
		}
		i++;
	}
	ft_memset(ret_cmd->args[tmp],'\0',2048);//controllare da qui
	return (ret_cmd);
}

/*
*/
void	trimmer(char *str)
{
	int	n;
	int	i;
	int	j;
	int	k;
	int	in_word;
	int	in_quote;
	char	quote_char;
	int l;

	n = ft_strlen(str);
	i = 0;
	while (i < n && ft_isspace(str[i])) {
		i++;
	}
	j = n - 1;
	while (j >= 0 && ft_isspace(str[j])) {
		j--;
	}
	k = 0;
	in_word = 0;
	in_quote = 0;
	quote_char = '\0';
	l = i;
	while (l <= j)
	{
		if (str[l] == '\'' || str[l] == '\"')
		{
			if (!in_quote) {
				in_quote = 1;
				quote_char = str[l];
			} else if (str[l] == quote_char) {
				in_quote = 0;
				quote_char = '\0';
			}
			str[k++] = str[l];
		} else if (!ft_isspace(str[l]) || (in_quote && ft_isspace(str[l]))) {
			str[k++] = str[l];
			in_word = 1;
		} else if (in_word) {
			str[k++] = ' ';
			in_word = 0;
		}
		l++;
	}
	if (str[k - 1] == '|')
		str[k - 1] = '\0';
	if (str[k - 2] == ' ')
		str[k - 2] = '\0';	
	str[k] = '\0';
	trimmer2(str);
}

/*
*/
void	trimmer2(char *str)
{
	int n;
	int i;
	int j;

	n = ft_strlen(str);
	i = 0;
	j = 0;
	while (i < n)
	{
		if (str[i] == '>' || str[i] == '<') {
		str[j++] = str[i++];
		if (i < n && (str[i] == '>' || str[i] == '<')) {
			str[j++] = str[i++];
		}
		while (i < n && ft_isspace(str[i])) {
			i++;
		}
		} else {
		str[j++] = str[i++];
		}
	}
	str[j] = '\0';
}
