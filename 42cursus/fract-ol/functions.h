/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:15:05 by ecoli             #+#    #+#             */
/*   Updated: 2023/02/08 15:25:32 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

//utils.c
int		ft_strncmp(const char *s1, const char *s2, size_t n);
double	atod(const char *str);
int		ft_isdigit(int c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
//draw.c
void	ft_mlx_draw(t_env *e);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		ft_mandelbrot(t_rend *area, int x, int y);
int		ft_julia(t_rend *area, int x, int y);
int		ft_burning_ship(t_rend *area, int x, int y);
int		ft_newton(t_rend *area, int x, int y);
//triggers.c
int		window_cross(t_env *e);
int		keyboard_manage(int key, t_env *e);
int		mouse_manage(int key, int x, int y, t_env *e);

#endif
