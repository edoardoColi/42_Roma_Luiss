/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triggers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 04:14:26 by eddy              #+#    #+#             */
/*   Updated: 2023/02/23 15:40:41 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

/*
key: Value of button pressed
x: Horizontal coordinate of when the key is pressed (wrt the mouse pointer)
y: Vertical coordinate of when the key is pressed (wrt the mouse pointer)
e: Structure with all the data
Captures a mouse keystroke by mapping it to the
key (the how is hidden).
*/
int	mouse_manage(int key, int x, int y, t_env *e)
{
//	The comment below can be removed to print the code of the keys that are pressed on the mouse. In this way you can configure the references present in global.h
//	printf("%d\n",key); 
	if (key == L_CLICK)
	{
		e->area.x_shift = ((x - (WIDTH / 2.0)) * (4.0 / WIDTH) * (1.0 / e->area.zoom)) + e->area.x_shift;
		e->area.y_shift = ((HEIGHT / 2.0) - y) * (4.0 / WIDTH) * (1.0 / e->area.zoom) + e->area.y_shift;
		ft_mlx_draw(e);
	}
	if (key == R_CLICK)
	{
		e->area.x_shift = 0.0;
		e->area.y_shift = 0.0;
		e->area.zoom = 0.55f;
		ft_mlx_draw(e);
	}
	if (key == UP_WHEEL)
	{
		e->area.x_shift = ((x - (WIDTH / 2.0)) * (4.0 / WIDTH) * (1.0 / e->area.zoom)) + e->area.x_shift; 	//These are used to zoom wrt the mouse position
		e->area.y_shift = ((HEIGHT / 2.0) - y) * (4.0 / WIDTH) * (1.0 / e->area.zoom) + e->area.y_shift;	//These are used to zoom wrt the mouse position
		e->area.zoom *= 2.0;
		ft_mlx_draw(e);
	}
	if (key == DOWN_WHEEL)
	{
		e->area.x_shift = ((x - (WIDTH / 2.0)) * (4.0 / WIDTH) * (1.0 / e->area.zoom)) + e->area.x_shift;	//These are used to zoom wrt the mouse position
		e->area.y_shift = ((HEIGHT / 2.0) - y) * (4.0 / WIDTH) * (1.0 / e->area.zoom) + e->area.y_shift;	//These are used to zoom wrt the mouse position
		e->area.zoom /= 2.0;
		ft_mlx_draw(e);
	}
	return (0);
}

/*
key: Value of button pressed
e: Structure with all the data
Captures a keyboard keystroke by mapping it to the
key (the how is hidden).
*/
int	keyboard_manage(int key, t_env *e)
{
//	The comment below can be removed to print the code of the keys that are pressed on the keyboard. In this way you can configure the references present in global.h
//	printf("%d\n",key);
	if (key == ESC)
	{
		mlx_destroy_image(e->mlx, e->img.image);
		mlx_destroy_window(e->mlx, e->mlx_win);
		mlx_destroy_display(e->mlx);											//May not be present as a function in other libraries (e.g. for iOS)
		free(e->mlx_win);
		free(e->mlx);
		write(out, "This seems to be the ESC\n", 26);
		exit(0);
	}
	if (key == C)
	{
		e->area.bw *= -1;
		ft_mlx_draw(e);
	}
	if (key == RX_ARROW)
	{
		e->area.x_shift = ((10) * (4.0 / WIDTH) * (1.0 / e->area.zoom)) + e->area.x_shift;
		e->area.y_shift = (0) * (4.0 / WIDTH) * (1.0 / e->area.zoom) + e->area.y_shift;
		ft_mlx_draw(e);
	}
	if (key == LX_ARROW)
	{
		e->area.x_shift = ((-10) * (4.0 / WIDTH) * (1.0 / e->area.zoom)) + e->area.x_shift;
		e->area.y_shift = (0) * (4.0 / WIDTH) * (1.0 / e->area.zoom) + e->area.y_shift;
		ft_mlx_draw(e);
	}
	if (key == UP_ARROW)
	{
		e->area.x_shift = ((0) * (4.0 / WIDTH) * (1.0 / e->area.zoom)) + e->area.x_shift;
		e->area.y_shift = (10) * (4.0 / WIDTH) * (1.0 / e->area.zoom) + e->area.y_shift;
		ft_mlx_draw(e);
	}
	if (key == DW_ARROW)
	{
		e->area.x_shift = ((0) * (4.0 / WIDTH) * (1.0 / e->area.zoom)) + e->area.x_shift;
		e->area.y_shift = (-10) * (4.0 / WIDTH) * (1.0 / e->area.zoom) + e->area.y_shift;
		ft_mlx_draw(e);
	}
	if (key == P)
	{
//	Nice function below to implement saving what is shown in the window in a local image(.jpeg)
//		save_as_jpeg("my_fractal", e);	//TODO
	}
	return (0);
}

/*
e: Structure with all the data
Implements closing the program when the
cross is pressed in the window.
*/
int	window_cross(t_env *e)
{
	mlx_destroy_image(e->mlx, e->img.image);
	mlx_destroy_window(e->mlx, e->mlx_win);
	mlx_destroy_display(e->mlx);												//May not be present as a function in other libraries (e.g. for iOS)
	free(e->mlx_win);
	free(e->mlx);
	write(out, "Just put a CROSS on it\n", 23);
	exit(0);
}
