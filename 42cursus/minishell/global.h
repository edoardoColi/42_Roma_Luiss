/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:20:10 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:53:49 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# include "libft/libft.h"

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>	//WHY
# include <termios.h>
# include <sys/wait.h>
# include <sys/ioctl.h>	//WHY
# include <sys/param.h>	//WHY
# include <errno.h>
# include <sys/types.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define CYEL "\033[0;33m"
# define CGRN "\033[0;32m"
# define CBRED "\033[1;31m"
# define CBGRN "\033[1;32m"
# define CBYEL "\033[1;33m"
# define CWHITE "\033[0m"

//per sigaction
//#define _POSIX_C_SOURCE 199309L
# define _POSIX_C_SOURCE 200809L	//WHY

//# define NAME_MAX 255	//WHY
//# define PATH_MAX 1024	//WHY
# define SUCCESS 0
# define FAIL 1

// Operators
# define PIPE 0
# define SQUOTE 1
# define DQUOTE 2
# define MQUOTE 3
# define REDIN 4
# define REDOUT 5
# define REDAPP 6
# define HERDOC 7
# define CASH 8
# define TILDE 9
# define NOCMD 10
# define EMPTY -1

// Errors
# define ERR_DIR 126
# define ERR_UNK 127

# define PROMPT ":"

//per far funzionare rl_replace_line
extern void	rl_replace_line(const char *text, int clear_undo);

typedef struct s_hellmini
{
	char				**env;

	char				*input;
	struct s_command	*current_cmd;

	int					exit_status;
	int					mc_pipes;
	int					mc_quotes;
	int					mc_wquotes;

}				t_hellmini;

typedef struct s_command
{
	char				*str;
	char				**tokens;
	int					spc[11];

	char				*command;
	char				**arguments;
	int					args_number;

	int					*red_type;
	char				**red;
	int					red_error;

	struct s_command	*next;
	struct s_command	*prev;

	t_hellmini			*shell;
}	t_command;

int			is_builtin(t_command *cmd);
int			redirector(t_command *cmd);
int			ms_exit(t_command *cmd);
int			unset(t_command *cmd);
int			echo(t_command *cmd);
int			env(t_command *cmd);
int			cd(t_command *cmd);
int			pwd(void);
void		expander(t_command *cmd);
char		*exp_tkn(char *str, char **env);
char		**ft_arrdup(char **arr);
void		init_shell(t_hellmini *shell, char **env);
t_command	*init_command(t_hellmini *shell);
void		set_ecode(int code);
void		control_c_signal(int sig);
void		free_commands(t_hellmini *shell);
void		free_shell(t_hellmini *shell);
int			parser(t_hellmini *sh);
int			lexer_init(t_hellmini *shell);
char		*split_operator(char *line, int *ff, int not_new);
char		*split_line(char *line);
void		free_arr(char **split_arr);
char		**ft_arrdup(char **arr);
char		*exp_tkn(char *str, char **env);
void		ft_sigs_handler(int sig);
void		control_slash(int sig);
char		**exp_(t_hellmini shell);
void		print_env_vars(char *env_cpy);
int			ft_strcmp_better(const char *s1, const char *s2);
void		alpha_sort(char **mtrx);
char		**export_aux(char **key_value, char **env_cpy);
int			ft_export(char **key_value, t_hellmini *shell);
void		add_string_to_env(t_hellmini *shell, char *str, char **env);
void		val_env_part_2(int *exist, char **str, char *arg);
int			export_compare_values(char *entry, char *arg);
char		**insert_values_env(char **args, char **env);
int			export_check_argument(char *str);
char		*our_prompt(t_hellmini *shell, char *str);
void		exec_redir_pipe(t_command *cmd, int *stdin, int *stdout);
void		exec_redir(t_command *cmd, int *stdin, int *stdout);
void		ft_execv(t_command *cmd, int *status);
void		stamp_no_file_error(char *file);

#endif
