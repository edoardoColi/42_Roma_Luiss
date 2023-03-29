#include "global.h"
#include "functions.h"

static void	ft_putstr_fd(char *s, int fd)
{
	int	a;

	a = 0;
	if (!s)
		return ;
	while (s[a])
	{
		write (fd, &s[a], 1);
		a++;
	}
	write(fd, "\n", 1);
}

int check_in(t_command *cmd)
{
   int  a;
   a = 0;
   while(cmd->rin_and_heredoc[a])
   {
		if(cmd->redin_type[a] == 0)
		{
			if(access(cmd->rin_and_heredoc[a] , R_OK  < 0))
				{
				ft_putstr_fd(cmd->rin_and_heredoc[a], 2); 
				ft_putstr_fd("No such file or directory", 2);
				return(1);
				}
		}
		a++;
		
	}
	return(0);
}

int redirect_o(t_command *cmd)
{
int a;
int b;
int opn_fd;
opn_fd = 0;
int orig_stdo;
orig_stdo = dup(1);

b = 0;
a = 0;
if(cmd->rout_and_append[0] != NULL)
{
	while(cmd->rout_and_append[a] != NULL)
	{
		if(cmd->redout_type[b] == 0)
		opn_fd = open(cmd->rout_and_append[a], O_WRONLY | O_CREAT | O_TRUNC , 0644); // 0 to check if is a normal redirection
	
		if(cmd->redout_type[b] == 1)
		opn_fd = open(cmd->rout_and_append[a], O_WRONLY | O_CREAT | O_APPEND , 0644); // 1 to check if it is an append redirection
		if (cmd->rout_and_append[a + 1])
		close(opn_fd);
		b++;
		if(opn_fd < 0)
		{
		perror("OPEN ERROR\n");
		return(1);
		}
		a++;
	  }
	dup2(opn_fd, 1);
}
return (orig_stdo);
}

int redirect_i(t_command *cmd)
{
	int a;

	a = 0;
	int fd;
	

	if(cmd->rin_and_heredoc[a] != NULL)
	{
		while (cmd->rin_and_heredoc[a])
		{
			 if(cmd->redin_type[a] == 1)
			heredoc(cmd, a);
			a++;
		}
		// printf("%s", cmd->rdr_in[a - 1]);
		// if (access(cmd->rdr_in[a - 1] , R_OK ) < 0) // resetteare a e ciclare di nuovo le rdr_in < per  vedere se qualche file non esiste
		// {
		//     write(2, "No such file or directory\n" ,26 );
		//     exit (1);
		// }
		if(check_in(cmd))
		exit(1);
		else if (cmd->redin_type[a -1] == 0)
		{
			fd = open(cmd->rin_and_heredoc[a - 1], O_RDONLY);
		if(fd < 0)
		{   
			perror("OPEN ERROR\n");
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
		perror("DUP OUT ERROR\n");  
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
			perror("DUP IN ERROR\n");  
			exit(1);
		}
	  
	close(fd[0]);
	return(0);
}

int heredoc(t_command *cmd, int a)
{
	char *str;
	char *del;
	char **buff;
	int c;
	int fd;
	c = 0;
	fd = open("tmp", O_WRONLY | O_CREAT | O_APPEND , 0644);
	del = cmd->rin_and_heredoc[a];
	int stdo_fd;
	stdo_fd = dup(1);
	buff = (char **) malloc(sizeof(char *) * 1000);
	while(1)
	{
		str = readline(">");
		if(strcmp(str, del) != 0)
			buff[c] = str;
		c++;
		if(strcmp(str, cmd->rin_and_heredoc[a]) == 0)
		{
			dup2(fd, 1);
			break ;
		}
	}

	buff[c] = NULL;
	c = 0;
		if(cmd->rin_and_heredoc[a + 1] == NULL)
		{
	   while(buff[c])
		{   
			printf("%s\n", buff[c]);  
			c++;
		}
		}
		dup2(stdo_fd, 1);
		close(fd);
		fd = open("tmp", O_RDONLY | O_CREAT | O_APPEND , 0644);
		if(cmd->rin_and_heredoc[a + 1] == NULL)
		{
			dup2(fd, 0);
		}
		free(buff);
	return (0);
}

int redirectionin_type(t_command *cmd)
{
	int a;
	a = 0;
	while(cmd->rin_and_heredoc[a])
	{
		if(strncmp(cmd->rin_and_heredoc[a], "<<", 2) == 0 )
		{
			// printf("im in11\n");
		cmd->redin_type[a] = 1;
		memmove(cmd->rin_and_heredoc[a], cmd->rin_and_heredoc[a] + 2, strlen(cmd->rin_and_heredoc[a]) - 2 + 1); // add memmove and string function of libft
		}
		else if(strncmp(cmd->rin_and_heredoc[a], "<", 1) == 0 )
		{
			// printf("im in22\n");
		cmd->redin_type[a] = 0;
		memmove(cmd->rin_and_heredoc[a], cmd->rin_and_heredoc[a] +1 , strlen(cmd->rin_and_heredoc[a]));
		}
		a++;
	}
		// printf("%s\n",cmd->rin_and_heredoc[0] );
		return(0);
}

int redirectionout_type(t_command *cmd)
{
	int a;
	a = 0;
	while(cmd->rout_and_append[a])
	{
		if(strncmp(cmd->rout_and_append[a], ">>", 2) == 0 ) //add libft strncmp
		{
			// printf("im in1\n");
		cmd->redout_type[a] = 1;
		memmove(cmd->rout_and_append[a], cmd->rout_and_append[a] + 2, strlen(cmd->rout_and_append[a]) - 2 + 1); // add memmove and string function of libft
		}
		 else if(strncmp(cmd->rout_and_append[a], ">", 1) == 0 )
		{
			// printf("im in2\n");
		cmd->redout_type[a] = 0;
		memmove(cmd->rout_and_append[a], cmd->rout_and_append[a]+1 , strlen(cmd->rout_and_append[a]));
		}
		a++;
	}
		// printf("%s\n",cmd->rout_and_append[0] );
		return(0);
}
