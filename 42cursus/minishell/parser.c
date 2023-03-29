/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by eddy              #+#    #+#             */
/*   Updated: 2023/03/30 01:03:27 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

static void	fill_spaces(char *str);
static void	trim_spaces(char *str);
static void	squeez_spaces(char *str);
static void	expand_cmd(char **str, char *env[]);
static void	replace_dollar_cmd(t_command *command, char *env[]);
static void	rem_quotes(t_command *command);

extern int g_toknow[2];

/*
*/
int		parser(char *cmds, int *n_cmds, char *env[])
{
	int			i;
	int			j;
	int			ret;
	int			pid_ret;
	pid_t		pid;
	t_command	*commands;

	ret = 0;
	commands = malloc(sizeof(t_command) * (*n_cmds));
	if (!commands)
	{
		perror("Fail malloc\n");
		free(env);
		exit(1);
	}
	//TODO controlla le malloc sotto, exit(1) mi basta per non fare le free?
	i = -1;
	while (++i < *n_cmds)	//allocate memory for the commands[i] arrays
	{
		commands[i].args = malloc(sizeof(char *) * MAX_ENTRY);
		commands[i].rin_and_heredoc = malloc(sizeof(char *) * MAX_ENTRY);
		commands[i].rout_and_append = malloc(sizeof(char *) * MAX_ENTRY);
		j = -1;
		while (++j < MAX_ENTRY)	//allocate memory for the commands[i].arrays strings
		{
			commands[i].args[j] = malloc(sizeof(char) * MAX_NAME);
			commands[i].rin_and_heredoc[j] = malloc(sizeof(char) * MAX_NAME);
			commands[i].rout_and_append[j] = malloc(sizeof(char) * MAX_NAME);
			ft_memset(commands[i].args[j], '\0', MAX_NAME);
			ft_memset(commands[i].rin_and_heredoc[j], '\0', MAX_NAME);
			ft_memset(commands[i].rout_and_append[j], '\0', MAX_NAME);
		}
		//SFARINA azzerare redin_type e redout_type?
		pipe(commands[i].fd);	//MOD inizializza fd
	}
	i = -1;
	while (++i < *n_cmds)
	{
		if (fill_cmd(&commands[i], i, cmds) != 0)
		{
			perror("Fail fill_cmd\n");
			i = -1;
			while (++i < *n_cmds)	//free loop for memory in the commands[i] arrays
			{
				j = -1;
				while (++j < MAX_ENTRY)	//free loop for memory in the commands[i].arrays strings
				{
					free(commands[i].args[j]);
					free(commands[i].rin_and_heredoc[j]);
					free(commands[i].rout_and_append[j]);
				}
				free(commands[i].args);
				free(commands[i].rin_and_heredoc);
				free(commands[i].rout_and_append);
			}
			free(commands);
			free(env);
			exit(1);
		}
////////////////DEBUG CMDs
		if(0){
			int p=0;
			int sbit=0;
			while(p<10)
			{
				if(commands[i].args[p] && sbit==0)
					printf("args '%-10s' %d-%d\n",commands[i].args[p],i,p);
				else
					sbit=1;
				p++;
			}
			p=0;sbit=0;
			while(p<10)
			{
				if(commands[i].rin_and_heredoc[p] && sbit==0)
					printf("rin_and_heredoc '%-10s' %d-%d\n",commands[i].rin_and_heredoc[p],i,p);
				else
					sbit=1;
				p++;
			}
			p=0;sbit=0;
			while(p<10)
			{
				if(commands[i].rout_and_append[p] && sbit==0)
					printf("rout_and_append '%-10s' %d-%d\n",commands[i].rout_and_append[p],i,p);
				else
					sbit=1;
				p++;
			}
		}
////////////////
	}
////////////////DEBUG ENV VAR
	if(0){
		printf("\nVARIABILI D'AMBIENTE\n\n");
		int p = 0;
		while (env[p] != NULL) {
			printf("%s\n", env[p]);
			p++;
		}
	}
///////////////
	i = -1;
	while (++i < *n_cmds)
	{
		redirectionout_type(&commands[i]);	//MOD
		redirectionin_type(&commands[i]);	//MOD
		replace_dollar_cmd(&commands[i], env);
		rem_quotes(&commands[i]);
		if (*n_cmds == 1 && commands[i].rout_and_append[0] == NULL && commands[i].rin_and_heredoc[0] == NULL)//MOD un solo comando + niente rio rot e cose varie
			ret = do_builtin(commands[i].args[0], commands[i].args, env, &commands);
		else
			ret = 2;
		if (ret == 2)	//il comando non e' builtin oppure e' in pipeline
		{
			pid = fork();
			if (pid == -1){
				perror("Fail fork\n");
				exit(1);
			}
			if (pid == 0) //processo figlio
			{
				if(commands[i].rout_and_append[0])						//MOD
					redirect_o(&commands[i]);							//MOD
				if(commands[i].rin_and_heredoc[0])						//MOD
					redirect_i(&commands[i]);							//MOD
				if(i > 0 && !commands[i].rin_and_heredoc[0])			//MOD
					pipe_in(commands[i - 1].fd);							//MOD
				if(i + 1 < *n_cmds && !commands[i].rout_and_append[0] )	//MOD
					pipe_out(commands[i].fd);									//MOD
				ret = do_builtin(commands[i].args[0], commands[i].args, env, &commands);
				if (ret == 2)	//il comando non e' builtin
				{
					expand_cmd(&(commands[i].args[0]), env);
					execve(commands[i].args[0], commands[i].args, env);
					printf("bash: %s: command not found\n", commands[i].args[0]);
					ret = 127;
				}
				i = -1;//loops to free the memory ot the new process generated by fork()
				while (++i < *n_cmds)	//free loop for memory in the commands[i] arrays
				{
					j = -1;
					while (++j < MAX_ENTRY)	//free loop for memory in the commands[i].arrays strings
					{
						free(commands[i].args[j]);
						free(commands[i].rin_and_heredoc[j]);
						free(commands[i].rout_and_append[j]);
					}
					free(commands[i].args);
					free(commands[i].rin_and_heredoc);
					free(commands[i].rout_and_append);
				}
				free(commands);
				i = -1;
				while (env[++i])
					free(env[i]);
				free(env);
				rl_clear_history();
				exit(ret);
			}
			else //processo padre
			{
				waitpid(pid, &pid_ret, 0);
				close(commands[i].fd[1]);	//MOD
				unlink("tmp");				//MOD
				if (WIFEXITED(pid_ret) && WEXITSTATUS(pid_ret) != 0)//figlio ritorna con exit()
					ret = WEXITSTATUS(pid_ret);
				else
					ret = 0;
			}
		}
	}
////////////////DEBUG CMDs
		if(0){
			int kk=-1;
			while(++kk<*n_cmds)
			{
				int p=0;
				int sbit=0;
				while(p<10)
				{
					if(commands[kk].args[p] && sbit==0)
						printf("args '%-10s' %d-%d\n",commands[kk].args[p],kk,p);
					else
						sbit=1;
					p++;
				}
				p=0;sbit=0;
				while(p<10)
				{
					if(commands[kk].rin_and_heredoc[p] && sbit==0)
						printf("rin_and_heredoc '%-10s' %d-%d\n",commands[kk].rin_and_heredoc[p],kk,p);
					else
						sbit=1;
					p++;
				}
				p=0;sbit=0;
				while(p<10)
				{
					if(commands[kk].rout_and_append[p] && sbit==0)
						printf("rout_and_append '%-10s' %d-%d\n",commands[kk].rout_and_append[p],kk,p);
					else
						sbit=1;
					p++;
				}
			}
		}
////////////////
	i = -1;
	while (++i < *n_cmds)	//free loop for memory in the commands[i] arrays
	{
		j = -1;
		while (++j < MAX_ENTRY)	//free loop for memory in the commands[i].arrays strings
		{
			free(commands[i].args[j]);
			free(commands[i].rin_and_heredoc[j]);
			free(commands[i].rout_and_append[j]);
		}
		free(commands[i].args);
		free(commands[i].rin_and_heredoc);
		free(commands[i].rout_and_append);
	}
	free(commands);
	return (ret);
}

/*
*/
int	fill_cmd(t_command *to_fill, int n_cmd, char *in_line)
{
	int			i;
	int			j;
	int			tmp[5];
	int			quote_rep;
	int			quotes_rep;
	char		arg_tmp[MAX_NAME];
	char		cmd[MAX_CMD];
	

	tmp[0] = -1;
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
		if (tmp[0] == n_cmd - 1)
		{
			cmd[j] = in_line[i];
			j++;
		}
		if (in_line[i] == '|' && quote_rep % 2 == 0 && quotes_rep % 2 == 0)
			tmp[0]++;
		if (tmp[0] == n_cmd)
			break ;
		i++;
	}
	cmd[j] = '\0';
	if (setup_spaces(cmd) != 0)
		return (1);
	i = 0;
	j = 0;
	quote_rep = 0;
	quotes_rep = 0;
	tmp[0] = 0;
	tmp[1] = 0;
	tmp[2] = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' && quotes_rep % 2 == 0)
			quote_rep++;
		if (cmd[i] == '"' && quote_rep % 2 == 0)
			quotes_rep++;
		if (cmd[i] == ' ' && quote_rep % 2 == 0 && quotes_rep % 2 == 0)
		{
			ft_strlcat(to_fill->args[tmp[0]], "\0", MAX_NAME);//non lo mette se sono alla fine perche non ho lo spazio
			(tmp[0])++;
			j = 0;
		}
		else
		{
			ft_strlcat(to_fill->args[tmp[0]], (char[]){cmd[i], '\0'}, MAX_NAME);//vado a inserire la singola lettera ma la vedo come stringa e non come char
			j++;
		}
		i++;
	}
	ft_strlcat(to_fill->args[tmp[0]], "\0", MAX_NAME);
	i = -1;
	j = tmp[0];
	tmp[0] = 0;
	while (++i <= j)	// loop per riempire rin_and_heredoc e rout_and_append
	{
		if (to_fill->args[i][0] == '<')//TODO se ho un heredoc deve partire 'getnextline' e li dentro tutte le variabili con il dollaro si espandono
		{
			ft_strlcat(to_fill->rin_and_heredoc[tmp[1]], to_fill->args[i], MAX_NAME);
			(tmp[1])++;
		}
		else if (to_fill->args[i][0] == '>')
		{
			ft_strlcat(to_fill->rout_and_append[tmp[2]], to_fill->args[i], MAX_NAME);
			(tmp[2])++;
		}
		else
		{
			ft_memset(arg_tmp, '\0', MAX_NAME);//pulisco prima di copiare sopra
			ft_strlcat(arg_tmp, to_fill->args[i], MAX_NAME);
			ft_memset(to_fill->args[tmp[0]], '\0', MAX_NAME);//pulisco prima di copiare sopra
			ft_strlcat(to_fill->args[tmp[0]], arg_tmp, MAX_NAME);
			(tmp[0])++;
		}
	}
	free(to_fill->args[tmp[0]]);	//libero perche senno mettendo a null perdo il riferimento
	to_fill->args[tmp[0]] = NULL;
	free(to_fill->rin_and_heredoc[tmp[1]]);	//libero perche senno mettendo a null perdo il riferimento
	to_fill->rin_and_heredoc[tmp[1]] = NULL;
	free(to_fill->rout_and_append[tmp[2]]);	//libero perche senno mettendo a null perdo il riferimento
	to_fill->rout_and_append[tmp[2]] = NULL;
	return (0);
}

/*
*/
int	setup_spaces(char *str)
{
	fill_spaces(str);
	trim_spaces(str);
	squeez_spaces(str);
	return (0);
}

/*
*/
static void	fill_spaces(char *str)
{
	int		i;
	int		j;
	int		len;
	char	new_str[MAX_CMD];

	len = ft_strlen(str);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (str[i] == '<' || str[i] == '>' || str[i] == '|') {
			new_str[j++] = ' ';
			new_str[j] = str[i];
			if (str[i+1] == str[i]) { // if the next character is also a '<', '>', or '|'
				new_str[++j] = str[i+1];
				i++; // skip the next character
			}
			new_str[++j] = ' ';
		} else if (str[i] == '"' || str[i] == '\'') {
			char quote = str[i];
			new_str[j] = str[i];
			while (i < len && str[++i] != quote) {
				new_str[++j] = str[i];
			}
			new_str[++j] = quote;
		} else {
			new_str[j] = str[i];
		}
		i++;
		j++;
	}
	new_str[j] = '\0';
	i = 0;
	while (new_str[i] != '\0')//loop per ricopiare la stringa
	{
		str[i] = new_str[i];
		i++;
	}
	str[i] = '\0';
}

/*
*/
static void	trim_spaces(char *str)
{
	int		i;
	int		j;
	int		k;
	int		len;
	int		in_word;
	int		in_quote;
	char	quote_char;

	len = ft_strlen(str);
	i = 0;
	while (i < len && ft_isspace(str[i])) {
		i++;
	}
	j = len - 1;
	while (j >= 0 && ft_isspace(str[j])) {
		j--;
	}
	k = 0;
	in_word = 0;
	in_quote = 0;
	quote_char = '\0';
	while (i <= j)
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (!in_quote) {
				in_quote = 1;
				quote_char = str[i];
			} else if (str[i] == quote_char) {
				in_quote = 0;
				quote_char = '\0';
			}
			str[k++] = str[i];
		} else if (!ft_isspace(str[i]) || (in_quote && ft_isspace(str[i]))) {
			str[k++] = str[i];
			in_word = 1;
		} else if (in_word) {
			str[k++] = ' ';
			in_word = 0;
		}
		i++;
	}
	if (str[k - 2] == ' ' && str[k - 1] == '|')
		str[k - 2] = '\0';	
	if (str[k - 1] == '|')
		str[k - 1] = '\0';
	str[k] = '\0';
}

/*
*/
static void	squeez_spaces(char *str)
{
	int i;
	int j;
	int n;

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
		}
		else
		{
			str[j++] = str[i++];
		}
	}
	str[j] = '\0';
}

/*
*/
static void	expand_cmd(char **str, char *env[])
{
	char	path[MAX_NAME];
	char	full_path[MAX_NAME];
	char	*dir;
	char	*cmd;
	char	*path_env;
	char	*saveptr;

	saveptr = NULL;
	cmd = *str;
	if (adhoc_getenv("PATH", env))
		path_env = adhoc_getenv("PATH", env);
	else
		return;// If the PATH environment variable isn't set, return
	ft_memset(path, '\0', MAX_NAME);//pulisco prima di usare
	ft_strlcat(path, path_env, MAX_NAME);
	dir = ft_strtok(path, ":", &saveptr);	// Tokenize the PATH variable by ':' char
	while (dir) {
		ft_memset(full_path, '\0', MAX_NAME);//pulisco prima di usare
		ft_strlcat(full_path, dir, MAX_NAME);
		ft_charcat(full_path, '/');
		ft_strlcat(full_path, cmd, MAX_NAME);
		if (access(full_path, X_OK) == 0)	// Check if the command exists in this directory
		{	
			*str = ft_strdup(full_path);// If it does, replace the command string with the full path
			free(dir);
			break;
		}
		free(dir);
		dir = ft_strtok(NULL, ":", &saveptr);// If not, move on to the next directory in the PATH
	}
}

/*
*/
static void	replace_dollar_cmd(t_command *command, char *env[])
{
	int		i;
	int		j;
	int		flag;
	int		quote;
	char	env_var[MAX_NAME];
	char	new_cmd[MAX_NAME];

	i = -1;
	while (command->args[++i])
	{
		ft_memset(new_cmd, '\0', MAX_NAME);//pulisco prima di copiare sopra
		ft_memset(env_var, '\0', MAX_NAME);//pulisco prima di copiare sopra
		j = -1;
		flag = 0;
		quote = 0;
		while (command->args[i][++j] != '\0')
		{
			if (command->args[i][j] == '\'')
				quote++;
			if (quote%2 == 0)
			{
				if (command->args[i][j] == '$')
				{
					j++;
					while ((adhoc_isalpha(command->args[i][j]) || command->args[i][j] == '?') && command->args[i][j] != '\0')
					{
						if (flag == 0)
							flag = 1;
						if (command->args[i][j] == '?' && env_var[0] == '\0')
						{
							ft_charcat(env_var, command->args[i][j]);
							break;
						}
						else if (command->args[i][j] == '?')
							break;
						else
							ft_charcat(env_var, command->args[i][j]);
						j++;
					}
					if (flag == 1)
					{
						if (env_var[0] == '?')
						{
							ft_strlcat(new_cmd, ft_itoa(g_toknow[0]), MAX_NAME);
							j++;
						}
						else if (adhoc_getenv(env_var, env))
							ft_strlcat(new_cmd, adhoc_getenv(env_var, env), MAX_NAME);
						flag = 0;
						ft_memset(env_var, '\0', MAX_NAME);//pulisco prima di riutilizzare
					}
				}
				if (command->args[i][j] == '$')
					j--;
				else
					ft_charcat(new_cmd, command->args[i][j]);
			}
			else
				ft_charcat(new_cmd, command->args[i][j]);
		}
		ft_memset(command->args[i], '\0', MAX_NAME);//pulisco prima di copiare sopra
		ft_strlcat(command->args[i], new_cmd, MAX_NAME);
	}
	i = -1;
	while (command->rin_and_heredoc[++i])
	{
		ft_memset(new_cmd, '\0', MAX_NAME);//pulisco prima di copiare sopra
		ft_memset(env_var, '\0', MAX_NAME);//pulisco prima di copiare sopra
		j = -1;
		flag = 0;
		quote = 0;
		while (command->rin_and_heredoc[i][++j] != '\0')
		{
			if (command->rin_and_heredoc[i][j] == '\'')
				quote++;
			if (quote%2 == 0)
			{
				if (command->rin_and_heredoc[i][j] == '$')
				{
					j++;
					while (adhoc_isalpha(command->rin_and_heredoc[i][j]) && command->rin_and_heredoc[i][j] != '\0')
					{
						if (flag == 0)
							flag = 1;
						if (command->rin_and_heredoc[i][j] == '?' && env_var[0] == '\0')
						{
							ft_charcat(env_var, command->rin_and_heredoc[i][j]);
							break;
						}
						else if (command->rin_and_heredoc[i][j] == '?')
							break;
						else
							ft_charcat(env_var, command->rin_and_heredoc[i][j]);
						j++;
					}
					if (flag == 1)
					{
						if (adhoc_getenv(env_var, env))
							ft_strlcat(new_cmd, adhoc_getenv(env_var, env), MAX_NAME);
						flag = 0;
						ft_memset(env_var, '\0', MAX_NAME);//pulisco prima di riutilizzare
					}
				}
				if (command->rin_and_heredoc[i][j] == '$')
					j--;
				else
					ft_charcat(new_cmd, command->rin_and_heredoc[i][j]);
			}
			else
				ft_charcat(new_cmd, command->rin_and_heredoc[i][j]);
		}
		ft_memset(command->rin_and_heredoc[i], '\0', MAX_NAME);//pulisco prima di copiare sopra
		ft_strlcat(command->rin_and_heredoc[i], new_cmd, MAX_NAME);
	}
	i = -1;
	while (command->rout_and_append[++i])
	{
		ft_memset(new_cmd, '\0', MAX_NAME);//pulisco prima di copiare sopra
		ft_memset(env_var, '\0', MAX_NAME);//pulisco prima di copiare sopra
		j = -1;
		flag = 0;
		quote = 0;
		while (command->rout_and_append[i][++j] != '\0')
		{
			if (command->rout_and_append[i][j] == '\'')
				quote++;
			if (quote%2 == 0)
			{
				if (command->rout_and_append[i][j] == '$')
				{
					j++;
					while (adhoc_isalpha(command->rout_and_append[i][j]) && command->rout_and_append[i][j] != '\0')
					{
						if (flag == 0)
							flag = 1;
						if (command->rout_and_append[i][j] == '?' && env_var[0] == '\0')
						{
							ft_charcat(env_var, command->rout_and_append[i][j]);
							break;
						}
						else if (command->rout_and_append[i][j] == '?')
							break;
						else
							ft_charcat(env_var, command->rout_and_append[i][j]);
						j++;
					}
					if (flag == 1)
					{
						if (adhoc_getenv(env_var, env))
							ft_strlcat(new_cmd, adhoc_getenv(env_var, env), MAX_NAME);
						flag = 0;
						ft_memset(env_var, '\0', MAX_NAME);//pulisco prima di riutilizzare
					}
				}
				if (command->rout_and_append[i][j] == '$')
					j--;
				else
					ft_charcat(new_cmd, command->rout_and_append[i][j]);
			}
			else
				ft_charcat(new_cmd, command->rout_and_append[i][j]);
		}
		ft_memset(command->rout_and_append[i], '\0', MAX_NAME);//pulisco prima di copiare sopra
		ft_strlcat(command->rout_and_append[i], new_cmd, MAX_NAME);
	}
}

/*
*/
static void	rem_quotes(t_command *command)
{
	int		i;
	int		j;
	int		flag;
	char	quote;
	char	new_cmd[MAX_NAME];

	i = -1;
	while (command->args[++i])
	{
		ft_memset(new_cmd, '\0', MAX_NAME);//pulisco prima di copiare sopra
		j = -1;
		flag = 0;
		quote = ' ';
		while (command->args[i][++j] != '\0')
		{
			if (command->args[i][j] == '\'' || command->args[i][j] == '"')
			{
				if (flag == 0)
				{
					flag = 1;
					quote = command->args[i][j];
				}
				else
				{
					if (command->args[i][j] == quote)
					{
						flag = 0;
						quote = ' ';
					}
					else
						ft_charcat(new_cmd, command->args[i][j]);
				}
			}
			else
				ft_charcat(new_cmd, command->args[i][j]);
		}
		ft_memset(command->args[i], '\0', MAX_NAME);//pulisco prima di copiare sopra
		ft_strlcat(command->args[i], new_cmd, MAX_NAME);
	}
	i = -1;
	while (command->rin_and_heredoc[++i])
	{
		ft_memset(new_cmd, '\0', MAX_NAME);//pulisco prima di copiare sopra
		j = -1;
		flag = 0;
		quote = ' ';
		while (command->rin_and_heredoc[i][++j] != '\0')
		{
			if (command->rin_and_heredoc[i][j] == '\'' || command->rin_and_heredoc[i][j] == '"')
			{
				if (flag == 0)
				{
					flag = 1;
					quote = command->rin_and_heredoc[i][j];
				}
				else
				{
					if (command->rin_and_heredoc[i][j] == quote)
					{
						flag = 0;
						quote = ' ';
					}
					else
						ft_charcat(new_cmd, command->rin_and_heredoc[i][j]);
				}
			}
			else
				ft_charcat(new_cmd, command->rin_and_heredoc[i][j]);
		}
		ft_memset(command->rin_and_heredoc[i], '\0', MAX_NAME);//pulisco prima di copiare sopra
		ft_strlcat(command->rin_and_heredoc[i], new_cmd, MAX_NAME);
	}
	i = -1;
	while (command->rout_and_append[++i])
	{
		ft_memset(new_cmd, '\0', MAX_NAME);//pulisco prima di copiare sopra
		j = -1;
		flag = 0;
		quote = ' ';
		while (command->rout_and_append[i][++j] != '\0')
		{
			if (command->rout_and_append[i][j] == '\'' || command->rout_and_append[i][j] == '"')
			{
				if (flag == 0)
				{
					flag = 1;
					quote = command->rout_and_append[i][j];
				}
				else
				{
					if (command->rout_and_append[i][j] == quote)
					{
						flag = 0;
						quote = ' ';
					}
					else
						ft_charcat(new_cmd, command->rout_and_append[i][j]);
				}
			}
			else
				ft_charcat(new_cmd, command->rout_and_append[i][j]);
		}
		ft_memset(command->rout_and_append[i], '\0', MAX_NAME);//pulisco prima di copiare sopra
		ft_strlcat(command->rout_and_append[i], new_cmd, MAX_NAME);
	}
}
