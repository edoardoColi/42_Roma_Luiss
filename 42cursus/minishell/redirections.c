#include "global.h"
#include "functions.h"

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
cmd->rdr_out[0] = "file1.txt";
cmd->rdr_out[1] = "file2.txt";
cmd->rdr_out[2] = "file3.txt";
cmd->rdr_out[3] = NULL;

if(cmd->rdr_out[0] != NULL)
{
    while(cmd->rdr_out[a] != NULL)
    {
        if(cmd->red_type[b] == 0)
        opn_fd = open(cmd->rdr_out[a], O_WRONLY | O_CREAT | O_TRUNC , 0644); // 0 to check if is a normal redirection
    
        if(cmd->red_type[b] == 1)
        opn_fd = open(cmd->rdr_out[a], O_WRONLY | O_CREAT | O_APPEND , 0644); // 1 to check if it is an append redirection
        if (cmd->rdr_out[a + 1])
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

int redirect_i(t_command *cmd)
{
    int a;

    a = 0;
    char    *rdr_in[100];
    int fd;
    cmd->rdr_in[0] = "file1.txt";
    cmd->rdr_in[1] = "file2.txt";
    cmd->rdr_in[2] = "file3.txt";
    cmd->rdr_in[3] = NULL;
    if(cmd->rdr_in[a])
    {
        while (cmd->rdr_in[a])
        {
            a++;
        }
        printf("%s", cmd->rdr_in[a - 1]);
        if (access(cmd->rdr_in[a - 1] , R_OK ) < 0)
        {
            write(2, "No such file or directory\n" ,25 );
        }
        else
        {
            fd = open(cmd->rdr_in[a - 1], O_RDONLY);
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

int pipeout(int fd[2])
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

int pipein(int fd[2])
{
    close(fd[1]);
    if ( dup2(fd[0], 0 )== - 1)
        {
            write(2,"DUP OUT ERROR\n", 14);  
            exit(1);
        }
      
    close(fd[0]);
    return(0);
}
//  int set_pipeline(t_command cmd, int i, int pipes[][2])
//  {

//  }