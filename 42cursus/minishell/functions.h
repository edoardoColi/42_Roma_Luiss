/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:15:05 by ecoli             #+#    #+#             */
/*   Updated: 2023/03/30 00:36:28 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

//parser.c
int			parser(char *cmd, int *n_cmd, char *env[]);
int			fill_cmd(t_command *cmdo, int n_cmds, char *in_line);
int			setup_spaces(char *str);
//analyzer.c
int			analyzer(char *cmd, int *n_cmd);
//utils.c
int			ft_isspace(char c);
int			adhoc_isalpha(int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			adhoc_setenv(const char *name, char *value, char *env[]);
void		*ft_memset(void *b, int c, size_t len);
char		*ft_strdup(char *str);
char		*adhoc_getenv(const char *name, char *env[]);
size_t		ft_strlen(const char *s);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_charcat(char *dst, const char src);
char		*ft_itoa(int n);
size_t		size_num(int n);
char		*ft_strtok(char *str, const char *delim, char **saveptr);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strchr(const char *str, int c);
void		dollar_replace(char *str, char *env[]);
//builtins.c
int			do_builtin(const char *path, char *const *argv, char *const *env, t_command **commands);
//redirections.c
int			redirect_o(t_command *cmd);
int			redirect_i(t_command *cmd);
int			pipe_out(int fd[2]);
int			pipe_in(int fd[2]);
int			heredoc(t_command *cmd, int a);
int			redirectionin_type(t_command *cmd);
int			redirectionout_type(t_command *cmd);
void		create_pipe(t_command *cmd, int a);
#endif
