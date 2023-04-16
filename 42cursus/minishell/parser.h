/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:19:36 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:06:27 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "global.h"

# define GRN "\033[1;32m"
# define WHITE "\033[0m"

void	before_write_word(t_command *cmd, int *argc, int *items);
void	write_redirection(t_command *cmd, char c1, char c2);
void	write_word(char *cnt, t_command *cmd);
void	fill_token(t_command *cmd, int *argc);
int		red_in_string(t_command *cmd, char *str, int red_n);
void	set_operator_flags(t_command *cmd, char *s, int *m);
int		exit_quotes_if_it_is_one(char *str, int i);
void	set_meta_flags(t_command *cmd, char c);
int		i_after_quote(char *str, int i, int *iw, int *in);
int		to_next_quote(char *str, int i, char quote);
void	ps_move_to_next_char(t_command *cmd);
int		until_space(const char *str);
int		items_in_string(char *str);

#endif