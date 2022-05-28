/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:15:05 by ecoli             #+#    #+#             */
/*   Updated: 2022/05/13 15:00:53 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

void	free_and_error_exit(char *error, long *listA, long *listB);
void	free_and_ifneeded_exit(int esc, long *listA, long *listB, long *listC);
void	fill_from_str(int dim, char *str, long listA[], long listB[]);
void	fill_from_args(int dim, char **args, long listA[], long listB[]);
void	debug_print_lists(int dim, long listA[], long listB[]);
long	to_int(char **freeifexit, int index, long listA[], long listB[]);
int		counter(char const *s, char c);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	push_swap(int dim, long listA[], long listB[]);
int		unicity(int len, long list[]);
int		arr_len(int dim, long list[]);
void	do_move(char *move, long listA[], long listB[], int dim);
long	*count_moves_to(int dim, long listA[], long listB[]);
int		better_move(int dim, long p[]);
long	*liss(int dim, long list[]);
int		is_in(int dim, long num, long list[]);
long	get_max(int dim, long list[]);
long	get_min(int dim, long list[]);
int		in_middle(long list[], long size, long val, long idx);
long	absolut(long n);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
int		special_case(int dim, long listA[]);
int		get_idx(int dim, long num, long list[]);
void	scroll(long list[], int dim, int direction);
long	*get_best_liss(int dim, long listA[], long listB[]);
void	final_order(int dim, long listA[], long listB[], long init_liss[]);

#endif