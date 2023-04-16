/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:05:56 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 14:22:46 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# define DEBUG 2
# define ERR "[\033[1;31mERROR\033[0m	]:"
# define INF "[\033[1;32mINFO\033[0m	]:"
# define SIG "[\033[1;33mSIGN\033[0m	]:"
# define WAR "[\033[1;33mWARN\033[0m	]:"

typedef struct s_pflags
{
	int		dimension;
	int		minus;
	int		plus;
	int		hash;
	int		space;
	int		zero;
	int		length;
	int		point;
	int		prec;
	char	type;
}				t_pflags;

int		ft_printfd(const char *str, ...);
int		ft_printf(const char *str, ...);
int		pfnd(const char *str, ...);
int		pfn(const char *str, ...);

// flag_utils.c
void	reset_struct(t_pflags *tf);
void	check_flags(t_pflags *tf);
char	*set_precision(char *str, t_pflags *tf);
char	*set_flags(char	*str, t_pflags *tf);

// put_things_aside.c
int		number_digits(long int n);
int		isdigitaft(int ch, char start);
void	pf_putchar_fd(char c, int fd, t_pflags *tf);
void	pf_putnbr_fd(long int n, int fd, t_pflags *tf);
size_t	pf_strlen(const char *str);

// base.c
void	stampa(char *str);
int		found_terminator(char c);
char	*find_percent(char *str);
void	print_previous_part(char *str, size_t max, t_pflags *tf);

// printers.c
void	print_element(t_pflags *tf, va_list valist);
void	print_c(char ch, t_pflags *tf);
void	print_s(char *str, t_pflags *tf);
void	print_i(int i, t_pflags *tf);
void	print_x(long int val, t_pflags *tf);
void	print_p(void *pointer, t_pflags *tf);
void	print_u(long int val, t_pflags *tf);
void	print_t(t_pflags *tf);
void	print_y(t_pflags *tf);
void	print_0s(int num, t_pflags *tf, char ch);
void	print_n0s(int n, char ch, t_pflags *tf);
void	print_hex_ptr(char *res, t_pflags *tf);

void	print_spaces_before(int n, t_pflags *tf);
void	print_spaces_after(int n, t_pflags *tf);
void	print_precision(int n, t_pflags *tf);
void	print_zeroes(int n, t_pflags *tf);

#endif
