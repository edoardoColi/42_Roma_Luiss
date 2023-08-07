/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triggers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 04:14:26 by eddy              #+#    #+#             */
/*   Updated: 2023/05/16 21:26:03 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "global.h"
#include "functions.h"

// /*
// key: Value of button pressed
// x: Horizontal coordinate of when the key is pressed (wrt the mouse pointer)
// y: Vertical coordinate of when the key is pressed (wrt the mouse pointer)
// s: Structure with all the data
// Captures a mouse keystroke by mapping it to the
// key (the how is hidden).
// */
int	mouse_manage(int key, int x, int y, t_scene *s)
{
//	The comment below can be removed to print the code of the keys that are pressed on the mouse. In this way you can configure the references present in global.h
//	printf("%d\n",key); 
	if (key == L_CLICK)
	{
		printf("Premuto L_CLICK\n");//DEBUG
		ft_mlx_draw(s);
	}
	if (key == R_CLICK)
	{
		printf("Premuto R_CLICK\n");//DEBUG
		ft_mlx_draw(s);
	}
	if (key == UP_WHEEL)
	{
		printf("Premuto UP_WHEEL\n");//DEBUG
		ft_mlx_draw(s);
	}
	if (key == DOWN_WHEEL)
	{
		printf("Premuto DOWN_WHEEL\n");//DEBUG
		ft_mlx_draw(s);
	}
	return (0);
}

// /*
// key: Value of button pressed
// s: Structure with all the data
// Captures a keyboard keystroke by mapping it to the
// key (the how is hidden).
// */
int	keyboard_manage(int key, t_scene *s)
{
//	The comment below can be removed to print the code of the keys that are pressed on the keyboard. In this way you can configure the references present in global.h
//	printf("%d\n",key);
	if (key == ESC)
	{
		mlx_destroy_image(s->mlx, s->img.image);
		mlx_destroy_window(s->mlx, s->mlx_win);
		mlx_destroy_display(s->mlx);											//May not be present as a function in other libraries/or maybe not (e.g. for iOS)
		// free(s->mlx_win);														//This cause error "double free detected"
		free(s->mlx);
		free_list(s);
		printf("This seems to be the ESC\n");
		exit(0);
	}
	if (key == C)
	{
		printf("Premuto C\n");//DEBUG
		ft_mlx_draw(s);
	}
	if (key == RX_ARROW)
	{
		printf("Premuto RX_ARROW\n");//DEBUG
		ft_mlx_draw(s);
	}
	if (key == LX_ARROW)
	{
		printf("Premuto LX_ARROW\n");//DEBUG
		ft_mlx_draw(s);
	}
	if (key == UP_ARROW)
	{
		printf("Premuto UP_ARROW\n");//DEBUG
		ft_mlx_draw(s);
	}
	if (key == DW_ARROW)
	{
		printf("Premuto DW_ARROW\n");//DEBUG
		ft_mlx_draw(s);
	}
	if (key == P)
	{
//	Nice function below to implement saving what is shown in the window in a local image(.jpeg)
//		save_as_jpeg("my_fractal", e);	//TODO
	}
	return (0);
}

/*
s: Structure with all the data
Implements closing the program when the
cross is pressed in the window.
*/
int	window_cross(t_scene *s)
{
	mlx_destroy_image(s->mlx, s->img.image);
	mlx_destroy_window(s->mlx, s->mlx_win);
	mlx_destroy_display(s->mlx);												//May not be present as a function in other libraries/or maybe not (e.g. for iOS)
	// free(s->mlx_win);															//This cause error "double free detected"
	free(s->mlx);
	free_list(s);
	printf("Just put a CROSS on it\n");
	exit(0);
}
