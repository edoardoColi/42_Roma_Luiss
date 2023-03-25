/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by eddy              #+#    #+#             */
/*   Updated: 2023/03/25 15:58:30 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

/*
*/


int redirect_out(t_command *cmd)
{
int a;
int b;
int opn_fd;
opn_fd = 0;
int orig_stdo;
orig_stdo = dup(1);

b = 0;
a = 0;
cmd->rout_and_append[0] = "file1.txt";
cmd->rout_and_append[1] = "file2.txt";
cmd->rout_and_append[2] = "file3.txt";
cmd->rout_and_append[3] = NULL;

if(cmd->rout_and_append[0] != NULL)
{
	while(cmd->rout_and_append[a] != NULL)
	{
		if(cmd->red_type[b] == 0)
		opn_fd = open(cmd->rout_and_append[a], O_WRONLY | O_CREAT | O_TRUNC , 0644); // 0 to check if is a normal redirection
	
		if(cmd->red_type[b] == 1)
		opn_fd = open(cmd->rout_and_append[a], O_WRONLY | O_CREAT | O_APPEND , 0644); // 1 to check if it is an append redirection
		if (cmd->rout_and_append[a + 1])
		close(opn_fd);
		b++;
		if(opn_fd < 0)
		{
		write(2, "OPEN ERROR\n", 11);
		return(1);
		}// putstr_fd("OPEN ERROR", 2);
		a++;
	  
	}
	dup2(opn_fd, 1);
}
return (orig_stdo);
}

int redirect_in(t_command *cmd)
{
	int a;

	a = 0;
	char    *rin_and_heredoc[100];
	int fd;
	cmd->rin_and_heredoc[0] = "file1.txt";
	cmd->rin_and_heredoc[1] = "file2.txt";
	cmd->rin_and_heredoc[2] = "file3.txt";
	cmd->rin_and_heredoc[3] = NULL;
	if(cmd->rin_and_heredoc[a])
	{
		while (cmd->rin_and_heredoc[a])
		{
			a++;
		}
		printf("%s", cmd->rin_and_heredoc[a - 1]);
		if (access(cmd->rin_and_heredoc[a - 1] , R_OK ) < 0)
		{
			write(2, "No such file or directory\n" ,25 );
		}
		else
		{
			fd = open(cmd->rin_and_heredoc[a - 1], O_RDONLY);
		if(fd < 0)
		{
			write(2, "OPEN ERROR\n", 11);
			return (1);
		}
			dup2(fd, 0);
		}
	}
	return (0);
}

int pipe_out(int fd[2])
{
	close(fd[0]);
	if ( dup2(fd[1], 1) == - 1)
	{
		write(2,"DUP OUT ERROR\n", 14);  
		exit(1);
	} 
	close(fd[1]);
	return(0);
}

int pipe_in(int fd[2])
{
	close(fd[1]);
	if ( dup2(fd[0], 0 )== - 1)
		{
			write(2,"DUP IN ERROR\n", 14);  
			exit(1);
		}
	  
	close(fd[0]);
	return(0);
}

// int set_pipeline(t_command cmd, int i, int pipes[][2])
// {

// }
