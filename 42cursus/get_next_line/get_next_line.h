/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 12:54:15 by ecoli             #+#    #+#             */
/*   Updated: 2022/03/25 17:58:40 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

char	*get_next_line(int fd);
int		attach_buffer(char **str, char *buffer[]);
int		str_len(char *s);
int		buf_len(char buf[]);
int		buf_nl_len(char buf[]);
void	l_shift_buf(char buffer[], int n);
void	l_shift_buf(char buffer[], int n);
int		check_line(char str[]);
char	*get_line_from_buf(char buffer[]);
char	*get_line_from_fd(int fd, char buffer[]);

#endif