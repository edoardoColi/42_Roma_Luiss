/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by eddy              #+#    #+#             */
/*   Updated: 2023/02/07 04:18:41 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

/*
*/
int		parser(char *cmd, int *n_cmd)
{
	int			i;
	char		*path;
	t_command	**command;

	printf("parso: %s\n",cmd);

	command = malloc(sizeof(t_command) * (*n_cmd));
	if (!command)
	{
		printf("Malloc fail\n");
		exit(1);
	}
	if (fill_cmds(&(*command), cmd, *n_cmd))
	{
		printf("fill_cmds fail\n");
		free(command);
		exit(1);
	}
	if (*n_cmd == 1)
	{
		path =  getenv("PATH");
	}
	else
		printf("MULTI-COMMAND NON ANCORA DISPONIBILE\n");

//for(int p=0;i<10;i++)
//printf("-- %s\n",command[0]->args[i]);

	/*char *command = strtok(cmd, " ");
	char *args[20];
	int i = 0;
	args[i++] = command;

	char *arg = strtok(NULL, " ");
	while (arg != NULL) {
		args[i++] = arg;
		arg = strtok(NULL, " ");
	}
	args[i] = NULL;

	char *dir = strtok(path, ":");
	while (dir != NULL) {
		char program_path[1000];
		sprintf(program_path, "%s/%s", dir, command);
printf("----QUI?,%s/%s\n",dir,command);

		if (access(program_path, X_OK) == 0) {
printf("----entro\n");

		int pid = fork();
		int status;
		if (pid == 0){//figlio
			ret = execve(program_path, args, NULL);//  the execve function does not expand environment variables because it runs the program in a completely separate process
			printf("qui non ci si deve arrivare\n");// qua sopra eseguo solo comandi
			return 1;
		}
		if (pid > 0){//padre
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				printf("Exit status del figlio %d\n",WIFEXITED(status));
		}
		else 
			printf("Fork error\n");


printf("----esco\n");
		}
printf("----PERCEH QUI?,%s/%s\n",dir,command);
		dir = strtok(NULL, ":");
printf("----PERCEH QUI222222?,%s/%s\n",dir,command);
	}*/


	
	return (0);
}

/*
*/
int	fill_cmds(t_command **c_list, char *in_line, int size)
{
	int	i;
	int	j;
	int	pos;

	pos = 0;
	i = 0;
	while(in_line[pos] != '\0')//TODO fare le prove che salta qualche lettera...
	{
		j = 0;
		while(in_line[pos] != '\0' && in_line[pos] != '|')
		{
			while (ft_isspace(in_line[pos]))
				pos++;
printf("(%d)",i);
printf("(%d)",j);
			while(in_line[pos] != '\0' && in_line[pos] != '|' && !isspace(in_line[pos]))
			{
				while (ft_isspace(in_line[pos]))
					pos++;
				printf("%c",in_line[pos]);
				pos++;
			}
			while (in_line[pos] == '|' || ft_isspace(in_line[pos]))
			{
			if (ft_isspace(in_line[pos]) && !ft_isspace(in_line[pos + 1]))
			{
	//			printf(" Quando tra %c e %c aumento j\n",in_line[pos],in_line[pos+1]);
				j++;
			}
			if (in_line[pos] == '|')
			{
	//			printf(" Cresce i e j = 0\n");
				i++;
				j = 0;
				pos++;
				while (ft_isspace(in_line[pos]))
					pos++;
			}
			pos++;
			}
		printf("\n");
		}
	}
	printf("\n");
	return (0);
}
