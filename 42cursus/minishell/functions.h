/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:15:05 by ecoli             #+#    #+#             */
/*   Updated: 2023/02/13 19:03:35 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

//parser.c
int			parser(char *cmd, int *n_cmd, char *envp[]);
void		trimmer(char *str);
void		trimmer2(char *str);
//analyzer.c
int			analyzer(char *cmd, int *n_cmd);
t_command	*fill_cmd(int c_num, char *in_line, char *envp[]);
//utils.c
void		*ft_memset(void *b, int c, size_t len);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
int			ft_isspace(char c);

#endif
