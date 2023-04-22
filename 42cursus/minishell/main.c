/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by eddy              #+#    #+#             */
/*   Updated: 2023/04/15 21:24:48 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

static void	handler(int sig, siginfo_t *siginfo, void *context);
static void	do_ps1(char *ps1, size_t len, char *env[]);
static int	insert_ps1(char *ps1, int p, const char *color);
static int	is_empty(char *str);

volatile int	g_toknow[2] = {0, 0};												//Global variable for {ret_val, n_cmds}

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
	(void)argc;																	//Cast for unused warning
	(void)argv;																	//Cast for unused warning
	int					i;
	int					n_cmd;
	char				ps1[2048];
	char				*in_line;
	char				*tmp;
	char				**my_env;
	struct sigaction	act;

	ft_memset(&act, '\0', sizeof(act));
	act.sa_sigaction = &handler;												//Meaningful only when estabilishing a signal handler. More in 'man sigaction'
	act.sa_flags = SA_SIGINFO;													//When the SA_SIGINFO flag is specified in act.sa_flags, the signal handler address is passed via the act.sa_sigaction field. This handler takes three arguments. More in 'man sigaction'
	sigemptyset(&act.sa_mask);
	if (sigaction(SIGINT, &act, NULL) == -1)									//Examine and change SIGINT signal action
	{
		perror("Fail sigaction(SIGINT)\n");
		return (1);
	}
	if (sigaction(SIGQUIT, &act, NULL) == -1)									//Examine and change SIGQUIT signal action
	{
		perror("Fail sigaction(SIGQUIT)\n");
		return (1);
	}
	my_env = malloc(sizeof(char *) * MAX_ENTRY);
	if (!my_env)
	{
		perror("Fail malloc\n");
		return (1);
	}
	i = -1;
	while (envp[++i])															//Loop to copy environment variables
		my_env[i] = ft_strdup(envp[i]);
	my_env[i] = NULL;
	do_ps1(ps1, 2048, my_env);
	tmp = ft_itoa(ft_atoi(adhoc_getenv("SHLVL", my_env)) + 1);					//Internally uses a malloc which will need to be freed
	adhoc_setenv("SHLVL", tmp, my_env);											//I change the environment variable shell level (SHLVL)
	free(tmp);
	in_line = readline(ps1);													//LEAKS Readline is null when is pressed ctrl-D (EOF), so we exit the while
	while (in_line != NULL)
	{
		if (!is_empty(in_line))
		{
			add_history(in_line);												//LEAKS
			if (analyzer(in_line, &n_cmd) == 0)
			{
				g_toknow[1] = n_cmd;
				g_toknow[0] = parser(in_line, &n_cmd, my_env);
			}
		}
		else
			g_toknow[0] = 0;
		free(in_line);
		do_ps1(ps1, 2048, my_env);
		in_line = readline(ps1);												//LEAKS Readline is null when is pressed ctrl-D (EOF), so we exit the while
	}
	i = -1;
	while (my_env[++i])															//Loop to free environment variables copy
		free(my_env[i]);
	free(my_env);
	rl_clear_history();
	printf("\n");
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
	(void)context;													//Cast for unused warning
	(void)siginfo;													//Cast for unused warning
	if (sig == SIGINT)												//Encoded in code 2
	{
		printf("\n");
		rl_on_new_line();//TODO questa se ho qualcosa aperto tipo 'cat' mi stampa doppio ps1
		rl_replace_line("", 0);
		rl_redisplay();
		g_toknow[0] = 130;
	}
	if (sig == SIGQUIT)												//Encoded in code 3
	{
		g_toknow[0] = 131;
	}
}

/*
str: String to analyze
Return 1 if is empty 0 otherwise.
Check if there is at least one character in the text that is not a space.
*/
static int	is_empty(char *str)
{
	int	i;

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
ps1: Reference to the string i want to build
len: Fixed length of the string
env: Reference to the environment used
Return none.
Inserts in the ps1 string what is necessary to print the string referring to PS1.
*/
static void	do_ps1(char *ps1, size_t len, char *env[])
{
	char	*pwd;
	char	*user;
	size_t	i;
	size_t	j;

	ft_memset(ps1, '\0', len);
	if (adhoc_getenv("USER", env))								//Check because it can return NULL
		user = adhoc_getenv("USER", env);
	else
		user = "";
	if (adhoc_getenv("PWD", env))								//Check because it can return NULL
		pwd = adhoc_getenv("PWD", env);
	else
		pwd = "";
	i = -1;
	if (g_toknow[0] == 0)
		i += insert_ps1(ps1, i + 1, "\U0001F607");				//Emoji angel face
	else
		i += insert_ps1(ps1, i + 1, "\U0001F608");				//Emoji devil face
	i += insert_ps1(ps1, i + 1, "\033[1;32m");					//Setup bold and green color
	j = -1;
	while (++i < len && user[++j] != '\0')
		ps1[i] = user[j];
	ps1[i] = '@';
	j = -1;
	i += insert_ps1(ps1, i, "\033[1;00m");						//Setup bold and white color
	ps1[i] = ':';
	i += insert_ps1(ps1, i + 1, "\033[1;34m");					//Setup bold and blue color
	j = -1;
	while (++i < len && pwd[++j] != '\0')
		ps1[i] = pwd[j];
	i += insert_ps1(ps1, i, "\033[1;00m");						//Setup bold and white color
	ps1[i] = '$';												//Setup user account type
	ps1[i + 1] = ' ';
}

/*
ps1: Reference to the string i want to build
p: Position of first empty slot of the string
color: String to indicate color in bash
Return the position after the last char.
Insert the size and color in the ps1 string.
*/
static int	insert_ps1(char *ps1, int p, const char *color)
{
	int	i;

	i = -1;
	while (color[++i] != '\0')
		ps1[p + i] = color[i];
	return (i);
}
