/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:15:39 by ecoli             #+#    #+#             */
/*   Updated: 2023/02/08 15:25:52 by ecoli            ###   ########.fr       */
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

# define WIDTH 480
# define HEIGHT 320

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

# define ITER_MAX 64

enum e_bool {
	false,
	true,
};

enum e_io {
	in,
	out,
	err,
};

typedef struct s_cpx
{
	double	re;
	double	im;
}	t_cpx;

typedef struct s_rend
{
	int		bw;
	t_cpx	fixed;
	double	zoom;
	double	x_shift;
	double	y_shift;
}	t_rend;

typedef struct s_data {
	void	*image;
	int		bpp;
	int		size_line;
	int		type;
	char	*data;
}	t_data;

typedef struct s_env {
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		(*ft_fractal)(t_rend *area, int x, int y);
	t_rend	area;
}	t_env;

#endif
