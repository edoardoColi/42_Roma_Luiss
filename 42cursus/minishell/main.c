/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by eddy              #+#    #+#             */
/*   Updated: 2023/03/25 03:41:07 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

static void	handler(int sig, siginfo_t *siginfo, void *context);
static void	do_ps1(char *ps1, size_t len, int mod, char *env[]);
static int	insert_ps1(char *ps1, int p, const char *color);
static int	is_empty(char *str);

volatile int toknow[2] = {0, 0};// {ret_val, n_cmds}

/*
WHERE:
struct sigaction {
	void (*sa_handler)(int);
	void (*sa_sigaction)(int, siginfo_t *, void *);
	sigset_t sa_mask;
	int sa_flags;
	void (*sa_restorer)(void);
}
*/
int	main(int argc, char *argv[], char *envp[])
{
	int					i;
	int					n_cmd;
	char				ps1[2048];
	char				*in_line;
	char				**my_env;
	struct sigaction	act;

	ft_memset(&act, '\0', sizeof(act));
	act.sa_sigaction = &handler;				//Meaningful only when estabilishing a signal handler. More in 'man sigaction'
	act.sa_flags = SA_SIGINFO;					//When the SA_SIGINFO flag is specified in act.sa_flags, the signal handler address is passed via the act.sa_sigaction field. This handler takes three arguments. More in 'man sigaction'
	sigemptyset(&act.sa_mask);
	if (sigaction(SIGINT, &act, NULL) == -1)	//Examine and change a signal action
	{
		perror("Fail sigaction(SIGINT)\n");
		return (1);
	}
	if (sigaction(SIGQUIT, &act, NULL) == -1)	//Examine and change a signal action
	{
		perror("Fail sigaction(SIGQUIT)\n");
		return (1);
	}
	my_env = malloc(sizeof(char*) * MAX_ENTRY);
	if (!my_env)
	{
		perror("Fail malloc\n");
		return (1);
	}
	i = -1;
	while (envp[++i])
		my_env[i] = ft_strdup(envp[i]);
	my_env[i] = NULL;
	do_ps1(ps1, 2048, toknow[0], my_env);

	//TEST memoria
	// in_line = "export ok=mia si=no forse=no bene=ok osk=as|env|unset si forse|env|cd ..|pwd|cat <ls > iao <<bene >>bale >ok bene dai";
	// n_cmd = 7;
	// parser(in_line, &n_cmd, my_env);

	while ( (in_line = readline(ps1)) != NULL)//per modificare questo faccio una stringa e metto quella
	{
		if (!is_empty(in_line))
		{
			add_history(in_line);
			toknow[1] = n_cmd;
			if (analyzer(in_line, &n_cmd) == 0)
				toknow[0] = parser(in_line, &n_cmd, my_env);
		}
		else
			toknow[0] = 0;
		free(in_line);
		do_ps1(ps1, 2048, toknow[0], my_env);
	}
	i = -1;
	while (my_env[++i])
		free(my_env[i]);
	free(my_env);
	printf("\n");//readline fallisce quando si preme ctrl-D (EOF) ergo usciamo dal while
	return (0);
}

/*
sig: Signal to handle.
siginfo: Buinld-in structure.
context:
Manages the signals received by the process
WHERE:
typedef struct {
	int si_signo;
	int si_code;
	union sigval si_value;
	int si_errno;
	pid_t si_pid;
	uid_t si_uid;
	void *si_addr;
	int si_status;
	int si_band;
} siginfo_t;
*/
static void	handler(int sig, siginfo_t *siginfo, void *context)
{
	(void)context;								//Cast for unused warning
	if (sig == SIGINT)//codice 2
	{
		printf("\n");
		rl_on_new_line();//TODO questa non se sono tipo con 'cat' senno ne vengono due
		rl_replace_line("", 0);
		rl_redisplay();
		toknow[0] = 130;
	}
	if (sig == SIGQUIT)//codice 3
	{//TODO questo solo se sono bloccato tipo con 'cat', se non ho scritto nulla non fa niente, senno quitta la shell(?)
		printf("Quit (core dumped)\n");
		toknow[0] = 131;//TODO non viene visto quando viene fatta la nuova riga
	}
}

/*
*/
static int	is_empty(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
*/
static void	do_ps1(char *ps1, size_t len, int mod, char *env[])
{
	char	*pwd;
	char	*user;
	char	*desktop_session;
	int		i;
	int		j;

	ft_memset(ps1, '\0', len);
	if (adhoc_getenv("USER", env))
		user = adhoc_getenv("USER", env);
	else
		user = "";
	if (adhoc_getenv("PWD", env))
		pwd = adhoc_getenv("PWD", env);
	else
		pwd = "";
	i = -1;
	if (mod == 0)
		i += insert_ps1(ps1, i + 1, "\U0001F607");//emoji angel face
	else
		i += insert_ps1(ps1, i + 1, "\U0001F608");//emoji devil face 
	i += insert_ps1(ps1, i + 1, "\033[1;32m");//grassetto e colore verde
	j = -1;
	while (++i < len && user[++j] != '\0')
		ps1[i] = user[j];
	ps1[i] = '@'; //cosi non devo fare -1 a i
	j = -1;
	i += insert_ps1(ps1, i, "\033[1;00m");//grassetto e colore bianco
	ps1[i] = ':';
	i += insert_ps1(ps1, i + 1, "\033[1;34m");//grassetto e colore blu
	j = -1;
	while (++i < len && pwd[++j] != '\0')
		ps1[i] = pwd[j];
	i += insert_ps1(ps1, i, "\033[1;00m");//grassetto e colore bianco
	ps1[i] = '$';//user account type
	ps1[i+1] = ' ';
}

/*
*/
static int insert_ps1(char *ps1, int p, const char *color)
{
	int i;

	i = -1;
	while (color[++i] != '\0')
		ps1[p + i] = color[i];
	return (i);
}
