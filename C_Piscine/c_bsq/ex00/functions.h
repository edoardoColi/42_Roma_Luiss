/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:29:21 by ebondi            #+#    #+#             */
/*   Updated: 2022/04/05 12:13:07 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

int		error(int n);
int		is_printable(char c);
void	free_matrix(int **matrix, int size);
int		**gen_file_tab(char *file, char *ebf, int *num_righe, int *len_righe);
int		first_look(char *file, int *len_r, char *ebf);
int		**crea_tab(int len_righe, int num_righe);
int		**riempi_tab(char *file, char *ebf, int num_righe, int len_righe);
int		check_first_line(char *file, int len_r1, int *num_righe, char *ebf);
int		trasforma(char c, char *ebf);
int		parse_first_line(char *str, char *ebf, int *num_righe);
int		my_atoi(char *str, int *num_righe);
int		my_ebf_cmp(char *ebf);
void	print_matrix(int **matrix, char *ebf, int num_righe, int len_righe);
int		**resolv_indian(int **tab, int num_righe, int len_righe);
int		min(int a, int b, int c);
int		**ridimensiona(int **tab, int max, int x, int y);
int		**chiudi(int **tab, int fd);
int		libera1(int n, int fd, char *line);
char	*tastiera(char *input);
void	step_back(int	**tab, int r,	int c);
void	assegna(int *arr, int i, int j);
void	prendi_input(void);

#endif
