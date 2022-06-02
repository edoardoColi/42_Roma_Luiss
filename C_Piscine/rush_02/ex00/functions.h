/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 19:01:13 by ecoli             #+#    #+#             */
/*   Updated: 2021/12/12 19:07:57 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

void	error(void);
void	error_diz(void);
int		my_atoi(char *str);
int		is_printable(char c);
void	see_diz(char *file, char *num);
char	**generate_file_tab(char *file, int num_righe);
t_nodo	*generate_diz(char **table, int num_righe);
int		get_righe(char *file);
t_nodo	*agg_ordinato_unico(int num, int decine, char *nome, t_nodo *succ);
char	**fill_tab(char *file, char **tab);
int		my_atoi2(char *str, int *ord);
char	*nome_key(char *str);
int		is_valid(char *str);
char	*tastiera(char *input);
int		stampa_num(t_nodo *succ, int n, int ex);
void	print_num(t_nodo *diz, char *num);
void	stampa_rec(t_nodo *diz, char *num, int size, int mod);
void	stampa_rec1(t_nodo *diz, char *num, int size);
void	stampa_rec2(t_nodo *diz, char *num, int size);
void	stampa_rec3(t_nodo *diz, char *num, int size);
void	stampa_rec4(t_nodo *diz, char *num, int size);
void	ft_putchar(char c);
void	ft_putstr(char *str);
int		ft_strlen(char *str);
int		main3(char *a);
int		main2(void);
void	libera_diz(t_nodo *succ);
void	libera_tab(char **tab, int num_righe);
int		my_atoi2_2(int n);

#endif
