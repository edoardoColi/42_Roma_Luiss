/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by eddy              #+#    #+#             */
/*   Updated: 2023/04/01 01:15:50 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

/*
cmd: String passed to bash on a single line
n_cmd: Reference to the total number of commands
Return 1 if an error occurr, 0 otherwise.
Verify that in the cmd string there are only the parameters that can
be subsequently analyzed by the program. As specified in the subject.
*/
int	analyzer(char *cmd, int *n_cmd)
{
	int	tmp;
	int	pos;
	int	or_rep;
	int	greater_rep;
	int	less_rep;
	int	quote_rep;
	int	quotes_rep;

	pos = 0;
	quote_rep = 0;
	quotes_rep = 0;
	*n_cmd = 1;
	while (*cmd == ' ' && *cmd != '\0')
		cmd++;
	while (cmd[pos] != '\0')
	{																		//Special character list
		if ((cmd[pos] == '!'													//Used for history expansion and negation of commands
			|| cmd[pos] == '#'													//Used to start a comment
			|| cmd[pos] == ';'													//Used to separate commands on the same line
			//&& 																//Multiples and(&) are not managed because under case of &
			//||																//Multiples or(|) are managed after
			|| cmd[pos] == '&'													//Used to run a command in the background
			|| cmd[pos] == '\\'													//Used to escape special characters, so they are treated as ordinary characters
			|| cmd[pos] == '('													//Used to group commands and control command execution
			|| cmd[pos] == ')'													//Used to group commands and control command execution
			|| cmd[pos] == '['													//Used to test attributes of files in test commands
			|| cmd[pos] == ']'													//Used to test attributes of files in test commands
			|| cmd[pos] == '{'													//Used to execute a list of commands in a subshell
			|| cmd[pos] == '}') && 												//Used to execute a list of commands in a subshell
			quotes_rep % 2 == 0 && quote_rep % 2 == 0)						//Can be used if they are inside the quotes
		{
			printf("minischell: special caracter (%c) unhandled\n\n", cmd[pos]);//Handled these special characters individually $ > < | << >> ' "
			return (2);
		}
		or_rep = -1;															//Checks for |
		tmp = 0;
		if (cmd[pos] == '|' && quotes_rep % 2 == 0 && quote_rep % 2 == 0)
		{
			*n_cmd = *n_cmd + 1;
			or_rep = 0;
			while (cmd[pos] != '\0')
			{
				if (cmd[pos] == '|')
					or_rep++;
				if (cmd[pos + 1] == '\0' || pos == 0)
				{
					printf("minischell: syntax error near unexpected token `|'\n");
					return (2);
				}
				if (ft_isspace(cmd[pos + 1]) || cmd[pos + 1] == '|')
				{	
					if (ft_isspace(cmd[pos + 1]))
						tmp = 1;
					if (cmd[pos + 1] == '|' && tmp == 1)
					{
						printf("minischell: syntax error near unexpected token `|'\n");
						return (2);
					}
					pos++;
				}
				else
					break ;
			}
		}
		if (or_rep == 2)
		{
			printf("minischell: special caracter (||) unhandled\n");
			return (2);
		}
		if (or_rep > 2)
		{
			printf("minischell: syntax error near unexpected token `|'\n");
			return (2);
		}
		greater_rep = -1;														//Checks for >
		tmp = 0;
		if (cmd[pos] == '>' && quotes_rep % 2 == 0 && quote_rep % 2 == 0)
		{
			greater_rep = 0;
			while (cmd[pos] != '\0')
			{
				if (cmd[pos] == '>')
					greater_rep++;
				if (cmd[pos + 1] == '\0')
				{
					printf("minischell: syntax error near unexpected token `newline'\n");
					return (2);
				}
				if (ft_isspace(cmd[pos + 1]) || cmd[pos + 1] == '>' || cmd[pos + 1] == '<' || cmd[pos + 1] == '|')
				{	
					if (ft_isspace(cmd[pos + 1]))
						tmp = 1;
					if (cmd[pos + 1] == '>' && tmp == 1)
					{
						printf("minischell: syntax error near unexpected token `>'\n");
						return (2);
					}
					if (cmd[pos + 1] == '<')
					{
						printf("minischell: syntax error near unexpected token `<'\n");
						return (2);
					}
					if (cmd[pos + 1] == '|')
					{
						printf("minischell: syntax error near unexpected token `|'\n");
						return (2);
					}
					pos++;
				}
				else
					break ;
			}
		}
		if (greater_rep == 3)
		{
			printf("minischell: syntax error near unexpected token `>'\n");
			return (2);
		}
		if (greater_rep > 3)
		{
			printf("minischell: syntax error near unexpected token `>>'\n");
			return (2);
		}
		less_rep = -1;															//Checks for <
		tmp = 0;
		if (cmd[pos] == '<' && quotes_rep % 2 == 0 && quote_rep % 2 == 0)
		{
			less_rep = 0;
			while (cmd[pos] != '\0')
			{
				if (cmd[pos] == '<')
					less_rep++;
				if (cmd[pos + 1] == '\0')
				{
					printf("minischell: syntax error near unexpected token `newline'\n");
					return (2);
				}
				if (ft_isspace(cmd[pos + 1]) || cmd[pos + 1] == '<' || cmd[pos + 1] == '>' || cmd[pos + 1] == '|')
				{	
					if (ft_isspace(cmd[pos + 1]))
						tmp = 1;
					if (cmd[pos + 1] == '<' && tmp == 1)
					{
						printf("minischell: syntax error near unexpected token `<'\n");
						return (2);
					}
					if (cmd[pos + 1] == '>')
					{
						printf("minischell: syntax error near unexpected token `>'\n");
						return (2);
					}
					if (cmd[pos + 1] == '|')
					{
						printf("minischell: syntax error near unexpected token `|'\n");
						return (2);
					}
					pos++;
				}
				else
					break ;
			}
		}
		if (less_rep == 3)
		{
			printf("minischell: unhandled case\n");
			return (2);
		}
		if (less_rep == 4)
		{
			printf("minischell: syntax error near unexpected token `<'\n");
			return (2);
		}
		if (less_rep == 5)
		{
			printf("minischell: syntax error near unexpected token `<<'\n");
			return (2);
		}
		if (less_rep > 5)
		{
			printf("minischell: syntax error near unexpected token `<<<'\n");
			return (2);
		}
		if (cmd[pos] == '\'' && quotes_rep % 2 == 0)							//Checks for '
			quote_rep++;
		if (cmd[pos] == '"' && quote_rep % 2 == 0)								//Checks for "
			quotes_rep++;
		pos++;
	}
	if (quote_rep % 2 != 0)
	{
		printf("minischell: not handled unclosed quote `''\n");
		return (2);
	}
	if (quotes_rep % 2 != 0)
	{
		printf("minischell: not handled unclosed quotes `\"'\n");
		return (2);
	}
	return (0);
}
