/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by eddy              #+#    #+#             */
/*   Updated: 2023/03/11 14:37:57 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

/*
*/
int	analyzer(char *cmd, int *n_cmd)
{
	int	or_rep;
	int	greater_rep;
	int	less_rep;
	int	quote_rep;
	int	quotes_rep;
	int tmp;
	int	pos;
	
	quote_rep = 0;
	quotes_rep = 0;
	pos = 0;
	*n_cmd = 1;
	while (cmd[pos] != '\0')
	{//lista dei caratteri speciali
		if ((cmd[pos] == '!' ||	//Used for history expansion and negation of commands
			cmd[pos] == '#' ||	//Used to start a comment
			cmd[pos] == ';' ||	//used to separate commands on the same line
			//&& and multipli non sono gestiti perche sotto caso di &
			//|| or multipli vengono gestiti dopo
			cmd[pos] == '&' ||	//Used to run a command in the background
			cmd[pos] == '\\' ||	//Used to escape special characters, so they are treated as ordinary characters
			cmd[pos] == '(' ||	//Used to group commands and control command execution
			cmd[pos] == ')' ||	//Used to group commands and control command execution
			cmd[pos] == '[' ||	//Used to test attributes of files in test commands
			cmd[pos] == ']' ||	//Used to test attributes of files in test commands
			cmd[pos] == '{' ||	//Used to execute a list of commands in a subshell
			cmd[pos] == '}') && //Used to execute a list of commands in a subshell
			quotes_rep % 2 == 0 && quote_rep % 2 == 0) //possono essere usati se interni alle quotes
		{
			printf("minischell: special caracter (%c) unhandled\n\n",cmd[pos]);//gestiti singolarmente questi caratteri speciali $ > < | << >> ' "
			return (2);
		}
		or_rep = -1;//controllo per |
		tmp = 0;
		if(cmd[pos] == '|' && quotes_rep % 2 == 0 && quote_rep % 2 == 0)
		{
			*n_cmd = *n_cmd + 1;
			or_rep = 0;
			while (cmd[pos] != '\0')
			{
				if(cmd[pos] == '|')
					or_rep++;
				if(cmd[pos + 1] == '\0' || pos == 0)
				{
					printf("minischell: syntax error near unexpected token `|'\n");
					return (2);
				}
				if(ft_isspace(cmd[pos + 1]) || cmd[pos + 1] == '|')
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
					break;
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
		greater_rep = -1;//controllo per >
		tmp = 0;
		if(cmd[pos] == '>' && quotes_rep % 2 == 0 && quote_rep % 2 == 0)
		{
			greater_rep = 0;
			while (cmd[pos] != '\0')
			{
				if(cmd[pos] == '>')
					greater_rep++;
				if(cmd[pos + 1] == '\0')
				{
					printf("minischell: syntax error near unexpected token `newline'\n");
					return (2);
				}
				if(ft_isspace(cmd[pos + 1]) || cmd[pos + 1] == '>' || cmd[pos + 1] == '<' || cmd[pos + 1] == '|')
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
					break;
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
		less_rep = -1;		//controllo per <
		tmp = 0;
		if(cmd[pos] == '<' && quotes_rep % 2 == 0 && quote_rep % 2 == 0)
		{
			less_rep = 0;
			while (cmd[pos] != '\0')
			{
				if(cmd[pos] == '<')
					less_rep++;
				if(cmd[pos + 1] == '\0')
				{
					printf("minischell: syntax error near unexpected token `newline'\n");
					return (2);
				}
				if(ft_isspace(cmd[pos + 1]) || cmd[pos + 1] == '<' || cmd[pos + 1] == '>' || cmd[pos + 1] == '|')
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
					break;
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
		if(cmd[pos] == '\'' && quotes_rep % 2 == 0)		//controllo per '
			quote_rep++;
		if(cmd[pos] == '"' && quote_rep % 2 == 0)		//controllo per "
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
