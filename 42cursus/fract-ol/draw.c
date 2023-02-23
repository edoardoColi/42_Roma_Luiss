/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 04:14:26 by eddy              #+#    #+#             */
/*   Updated: 2023/02/23 15:11:30 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

/*
env: Structure with all the data
Return none.
Calculates the color of each pixel and then represents it in the window.
*/
void	ft_mlx_draw(t_env *env)
{
	int	x;
	int	y;
	int	iterations;
	int	color;

	x = -1;
	y = -1;
	mlx_clear_window(env->mlx, env->mlx_win);
	while (++x < WIDTH)
	{
		while (++y < HEIGHT)
		{
			iterations = env->ft_fractal(&env->area, x, y);
			color = iterations * 255;
			if (env->area.bw == 1)
				color = color / ITER_MAX << 16 | color / ITER_MAX << 8 | color / ITER_MAX;
			else
				color = color << 15 | (color / 20) << 8 | color << 2;
			my_mlx_pixel_put(&env->img, x, y, color);
		}
		y = -1;
	}
	my_mlx_pixel_put(&env->img, WIDTH / 2, HEIGHT / 2, 0x00FF0000);				//Color the central pixel of the window red(0x00FF0000)
	mlx_put_image_to_window(env->mlx, env->mlx_win, env->img.image, 0, 0);
}

/*
data: Image structure
x: Pixel coordinate
y: Pixel coordinate
color: Color to give to the pixel
Return none.
Given the structure of the image, it changes the color of the pixel at x,y coordinates.
*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->data + (y * data->size_line + x * (data->bpp / 8));				//Line length differs from the actual window width. We therefore should ALWAYS calculate the memory offset using the line length set by mlx_get_data_addr
	*(unsigned int *)dst = color;												//Color is the hex representation of ARGB(a,r,g,b) acronym of Alpha Red Green Blue
}

/*
area: Structure for rendering options
x: Coordinates to compute
y: Coordinates to compute
Return the number of iterations.
Calculate the number of iterations necessary to establish
whether the point x,y converges or not according to the succession (z_n+1 = z_n^2 + c).
*/
int	ft_mandelbrot(t_rend *area, int x, int y)
{
	int			itr;
	t_cpx		z;
	t_cpx		c;
	t_cpx		tmp;

	itr = 0;
	z.re = area->fixed.re;														//Set the initial value of z = 0, as defined
	z.im = area->fixed.im;														//Set the initial value of z = 0, as defined
	c.re = ((x - (WIDTH / 2.0)) * (4.0 / WIDTH) * (1.0 / area->zoom)) + area->x_shift;		//Map the corresponding pixel of the window with the part of the plane that we want to measure
	c.im = (((HEIGHT / 2.0) - y) * (4.0 / WIDTH) * (1.0 / area->zoom)) + area->y_shift;		//Adjust everything based on the position of the center and the zoom factor
	while (itr < ITER_MAX)
	{
		tmp.re = pow(z.re, 2) - pow(z.im, 2) + c.re;
		tmp.im = 2.0 * z.re * z.im + c.im;
		if (sqrt(pow(tmp.re, 2) + pow(tmp.im, 2)) > 2.0)						//If the modulus, or magnitude, is greater than 2 then it diverges
			break ;																//Therefore it belongs to Mandelbrot Set
		z.re = tmp.re;
		z.im = tmp.im;
		itr++;
	}
	return (itr);
}

/*
area: Structure for rendering options
x: Coordinates to compute
y: Coordinates to compute
Return the number of iterations.
Calculate the number of iterations necessary to establish
whether the point x,y converges or not according to the succession (z_n+1 = z_n^2 + c).
*/
int	ft_julia(t_rend *area, int x, int y)
{
	int			itr;
	t_cpx		z;
	t_cpx		c;
	t_cpx		tmp;

	itr = 0;
	c.re = area->fixed.re;														//Set the initial value of c
	c.im = area->fixed.im;														//Set the initial value of c
	z.re = ((x - (WIDTH / 2.0)) * (4.0 / WIDTH) * (1.0 / area->zoom)) + area->x_shift;		//Map the corresponding pixel of the window with the part of the plane that we want to measure
	z.im = (((HEIGHT / 2.0) - y) * (4.0 / WIDTH) * (1.0 / area->zoom)) + area->y_shift;		//Adjust everything based on the position of the center and the zoom factor
	while (itr < ITER_MAX)
	{
		tmp.re = pow(z.re, 2) - pow(z.im, 2) + c.re;
		tmp.im = 2.0 * z.re * z.im + c.im;
		if (sqrt(pow(tmp.re, 2) + pow(tmp.im, 2)) > 2.0)						//If the modulus, or magnitude, is greater than 2 then it diverges
			break ;																//Therefore it belongs to Julia Set
		z.re = tmp.re;
		z.im = tmp.im;
		itr++;
	}
	return (itr);
}

/*
area: Structure for rendering options
x: Coordinates to compute
y: Coordinates to compute
Return the number of iterations.
Calculate the number of iterations necessary to establish
whether the point x,y converges or not according to the succession (z_n+1 = (|z_n.re| + i*|z_n.img|)^2 + c).
*/
int	ft_burning_ship(t_rend *area, int x, int y)
{
	int			itr;
	t_cpx		z;
	t_cpx		c;
	t_cpx		tmp;

	itr = 0;
	z.re = area->fixed.re;														//Set the initial value of z
	z.im = area->fixed.im;														//Set the initial value of z
	c.re = ((x - (WIDTH / 2.0)) * (4.0 / WIDTH) * (1.0 / area->zoom)) + area->x_shift;		//Map the corresponding pixel of the window with the part of the plane that we want to measure
	c.im = (((HEIGHT / 2.0) - y) * (4.0 / WIDTH) * (1.0 / area->zoom)) + area->y_shift;		//Adjust everything based on the position of the center and the zoom factor
	while (itr < ITER_MAX)
	{
		tmp.re = pow(z.re, 2) - pow(z.im, 2) + c.re;
		tmp.im = 2.0 * z.re * z.im + c.im;
		if (sqrt(pow(tmp.re, 2) + pow(tmp.im, 2)) > 2.0)						//If the modulus, or magnitude, is greater than 2 then it diverges
			break ;
		z.re = fabs(tmp.re);
		z.im = fabs(tmp.im);
		itr++;
	}
	return (itr);
}

/*
area: Structure for rendering options
x: Coordinates to compute
y: Coordinates to compute
Return the number of iterations.
Calculate the number of iterations necessary to establish
whether the point x,y converges or not according to the Newton succession (z_n+1 =z_n - F(z_n)/F'(z_n)).
*/
int	ft_newton(t_rend *area, int x, int y)
{
	int			itr;
	t_cpx		z;
	t_cpx		tmp;

	itr = 0;
	z.re = ((x - (WIDTH / 2.0)) * (4.0 / WIDTH) * (1.0 / area->zoom)) + area->x_shift;
	z.im = (((HEIGHT / 2.0) - y) * (4.0 / WIDTH) * (1.0 / area->zoom)) + area->y_shift;
	while (itr < 256)
	{
		if (1)	//Forced choice
		{		//Not really Newton but this -> z_n+1 =z_n^2 - (1, z_n.im)
			tmp.re = z.re * z.re - z.im * z.im - 1;
			tmp.im = 2 * z.re * z.im + z.im;
		}
		else
		{		//Not really Newton but this -> z_n+1 = (exp(z_n.re) * cos(z_n.im) - 1 , exp(z_n.re) * sin(z_n.im))
			tmp.re = exp(z.re) * cos(z.im) - 1;
			tmp.im = exp(z.re) * sin(z.im);
		}
		if (z.re * z.re - z.im * z.im > 4.0)//The escape distance can't be applied to Newton's fractals as well as to Mandelbrot's, so I made one at random
			break ;
		z.re = tmp.re;
		z.im = tmp.im;
		itr++;
	}
	return (itr);
}
