/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:16:47 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:06:27 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line.h"

# define DEBUGGING 0

# define TRUE 1
# define FALSE 0

# define MAXINT 2147483647
# define MININT -2147483648
# define MAXUINT 4294967295

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

int		ft_isalnum(int ch);
int		ft_isalpha(int ch);
int		ft_isascii(int ch);
int		ft_isdigit(int ch);
int		ft_isprint(int ch);
int		ft_tolower(int ch);
int		ft_toupper(int ch);
int		ft_atoi(const char *str);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strjoin_free(char *s1, char *s2, int f1, int f2);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char	*ft_itoa(int n);
char	**ft_split(const char *s, char c);

void	ft_bzero(void *s, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	*ft_calloc(size_t nmem, size_t size);
void	*ft_memcpy(void *des, const void *src, size_t n);
void	*ft_memmove(void *des, const void *src, size_t len);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);

size_t	ft_strlen(const char *str);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

//Bonus Part
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
int		ft_lstsize(t_list *lst);

//Further implemented functions
int		ft_issign(char ch);
int		ft_str_is_int(const char *str);
long	ft_atol(const char *str);
int		ft_duplicated_s_element(char **mat);
int		ft_duplicated_i_element(int	*array);
int		*ft_fill_i_array(char **mat, long size);
int		ft_strrncmp(const char *s1, const char *s2, int n);
void	ft_free_cmatrix(char **mtx);
void	ft_free_imatrix(int **mtx);
//void	ft_free_array(int *array);
long	ft_pow(int num, int n);
int		ft_module(int n);
int		ft_sqrt(long num);
int		ft_isspace(int c);
int		ft_isnotspace(int c);
char	ft_isquote(char ch);
char	ft_isredirection(char ch);
void	ft_filliarrayto_n(int *arr, int val, int n);
void	ft_free_ptr(void *ptr);
char	**ft_arrdup(char **arr);
void	ft_print_matrix(char **mtx);
size_t	ft_cmtxlen(char **mtx);
size_t	ft_arrlen(int *array);

// String Ptr Manipulation
char	**ft_reset_cptr(char **str, int status);
void	ft_move_n_cptr(char **str, size_t n);
void	ft_move_cptr(char **str);
void	ft_init_cptr(char **str);

#endif
