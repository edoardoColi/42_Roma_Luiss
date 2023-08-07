/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:15:05 by ecoli             #+#    #+#             */
/*   Updated: 2023/05/23 22:41:53 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

//utils.c
void	versor_to_matrix(float x, float y, float z, float matrix[3][3]);
double	dist_3d(t_3dp a, t_3dp b);
t_3dp	calc_versor(t_3dp from, t_3dp to);
int		argb_to_int(t_3dp a, int r, int g, int b);
void	error_msg(char *prog);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_adhoc_atoi(char *str);
double	ft_atod(const char *str);
double	ft_adhoc_atod(char *str);
void	*ft_memset(void *b, int c, size_t len);
int		ft_isdigit(int c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_strchr(const char *s, int c);
int		ft_isspace(char c);
char	*ft_strtok_and_trimm_spaces(char *str, const char *delim, char **saveptr);
void	debug_list_print(t_scene *s);
int		allocate_obj(t_obj *obj);
void	free_list(t_scene *s);
void	deallocate_obj(t_obj *obj);
//draw.c
void	ft_mlx_draw(t_scene *e);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		color_from_intersez(t_obj **head, t_3dp line_point, t_3dp line_versor);//TODO tentativo2
t_3dp	light_tracing(t_obj **head, double p_x, double p_y, double p_z);
//triggers.c
int		window_cross(t_scene *e);
int		keyboard_manage(int key, t_scene *e);
int		mouse_manage(int key, int x, int y, t_scene *e);
//checker.c
int		data_checker(int fd, t_scene *s);
int		fill_amb_light_scene(t_obj **head, char* parameter2, char* parameter1);
int		fill_cam_scene(t_obj **head, char* parameter1, char* parameter2, char* parameter3);
int		fill_light_scene(t_obj **head, char* parameter1, char* parameter2, char* parameter3);
int		fill_sphere_scene(t_obj **head, char* parameter1, char* parameter2, char* parameter3);
int		fill_plane_scene(t_obj **head, char* parameter1, char* parameter2, char* parameter3);
int		fill_cylinder_scene(t_obj **head, char* parameter1, char* parameter2, char* parameter3, char* parameter4, char* parameter5);

#endif
