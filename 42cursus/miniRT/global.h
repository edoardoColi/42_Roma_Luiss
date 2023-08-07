/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:15:39 by ecoli             #+#    #+#             */
/*   Updated: 2023/05/24 00:04:09 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>

# include "mlx.h"

# define WIDTH 1280
# define HEIGHT 1280
# define RATIO 64									//Ratio of 3d space and viewport 2d space (1:RATIO)

# define ESC 65307
# define C 99
# define P 112
# define RX_ARROW 65363
# define LX_ARROW 65361
# define UP_ARROW 65362
# define DW_ARROW 65364

# define L_CLICK 1
# define R_CLICK 3
# define UP_WHEEL 4
# define DOWN_WHEEL 5

# define MY_PI 3.14159265358979323846

enum e_bool {
	false,
	true,
};

enum e_io {
	in,
	out,
	err,
};

typedef struct s_3dp
{
	double	x;
	double	y;
	double	z;
}	t_3dp;

typedef struct s_obj
{
	char			*identifier;
	int				*colorRGB[3];
	t_3dp			*mass_center;
	t_3dp			*versor;
	double			*fov;								//Horizontal field of view
	double			*height;
	double			*radius;
	double			*light_ratio;
	struct s_obj	*next;
}	t_obj;

typedef struct s_data {
	void	*image;
	int		bpp;
	int		size_line;
	int		type;
	char	*data;
}	t_data;

typedef struct s_scene {
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	double	dist_viewport;
	t_obj	*head_list;
}	t_scene;

#endif

// #include <stdio.h>
// #include <math.h>


// void calculate_viewport_corners(float cam_x, float cam_y, float cam_z,
//                                 float fov_deg, int width, float aspect_ratio,
//                                 float *top_left, float *top_right,
//                                 float *bottom_left, float *bottom_right) {
//     // Calculate direction vector from camera position towards origin
//     float dir_x = 0 - cam_x;
//     float dir_y = 0 - cam_y;
//     float dir_z = 0 - cam_z;
//     float dir_len = sqrt(dir_x * dir_x + dir_y * dir_y + dir_z * dir_z);
//     float view_dir_x = -dir_x / dir_len;
//     float view_dir_y = -dir_y / dir_len;
//     float view_dir_z = -dir_z / dir_len;

//     // Calculate half-angle of horizontal FOV
//     float fov_rad = fov_deg * PI / 180.0f;
//     float half_angle = fov_rad / 2.0f;

//     // Calculate distance from camera position to viewport
//     float distance = (width / 2.0f) / tanf(half_angle);

//     // Calculate viewport height based on aspect ratio
//     float height = width / aspect_ratio;

//     // Calculate orthogonal vectors pointing right and up
//     float right_x = view_dir_z / sqrt(view_dir_x * view_dir_x + view_dir_z * view_dir_z);
//     float right_y = 0;
//     float right_z = -view_dir_x / sqrt(view_dir_x * view_dir_x + view_dir_z * view_dir_z);

//     float up_x = -view_dir_y * right_z;
//     float up_y = view_dir_z * right_x - view_dir_x * right_z;
//     float up_z = view_dir_x * right_y - view_dir_y * right_x;
//     float up_len = sqrt(up_x * up_x + up_y * up_y + up_z * up_z);
//     up_x /= up_len;
//     up_y /= up_len;
//     up_z /= up_len;

//     // Calculate corners of viewport relative to camera position
//     float half_width = width / 2.0f;
//     float half_height = height / 2.0f;

//     top_left[0] = cam_x + view_dir_x * distance - right_x * half_width + up_x * half_height;
//     top_left[1] = cam_y + view_dir_y * distance - right_y * half_width + up_y * half_height;
//     top_left[2] = cam_z + view_dir_z * distance - right_z * half_width + up_z * half_height;

//     top_right[0] = cam_x + view_dir_x * distance + right_x * half_width + up_x * half_height;
//     top_right[1] = cam_y + view_dir_y * distance + right_y * half_width + up_y * half_height;
//     top_right[2] = cam_z + view_dir_z * distance + right_z * half_width + up_z * half_height;

//     bottom_left[0] = cam_x + view_dir_x * distance - right_x * half_width - up_x * half_height;
//     bottom_left[1] = cam_y + view_dir_y * distance - right_y * half_width - up_y * half_height;
//     bottom_left[2] = cam_z + view_dir_z * distance - right_z * half_width - up_z * half_height;

//     bottom_right[0]...
