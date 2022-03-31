/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:57:59 by ecoli             #+#    #+#             */
/*   Updated: 2022/03/31 13:36:01 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

//Part Global
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

enum e_io {
	in,
	out,
	err,
};

//Part Functions
int		ft_printf(const char *str, ...);
void	switch_case(char c, va_list ap, ssize_t *count);
void	case_char(int c, ssize_t *count);
void	case_string(char *s, ssize_t *count);
void	case_void(void *p, ssize_t *count);
void	case_decimal(int d, ssize_t *count);
void	case_integer(int i, ssize_t *count);
void	case_u_decimal(unsigned int u, ssize_t *count);
void	case_hex_lowcase(unsigned int xlo, ssize_t *count);
void	case_hex_upcase(unsigned int xup, ssize_t *count);
void	case_perc(char perc, ssize_t *count);

#endif
