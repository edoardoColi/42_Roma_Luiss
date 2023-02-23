/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 04:14:26 by eddy              #+#    #+#             */
/*   Updated: 2023/02/23 15:45:24 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

static int	parser(int argc, char *argv[], t_env *e);
static void	usage(char *prog);

/*
*/
int	main(int argc, char *argv[])
{
	t_env	env;																//Contains all the information

	if (parser(argc, argv, &env))
	{
		usage(argv[0]);
		return (1);
	}
	env.mlx = mlx_init();
	env.mlx_win = mlx_new_window(env.mlx, WIDTH, HEIGHT, "fract-ol\t\tby ecoli");
	write(out, "Welcome. Stay ready to discover...\n", 35);
	env.img.image = mlx_new_image(env.mlx, WIDTH, HEIGHT);
	env.img.data = mlx_get_data_addr(env.img.image, &env.img.bpp, &env.img.size_line, &env.img.type);
	env.area.x_shift = 0.0;
	env.area.y_shift = 0.0;
	env.area.zoom = 1.0f;
	env.area.bw = 1;
	ft_mlx_draw(&env);
	mlx_hook(env.mlx_win, 17, 0, window_cross, &env);							//Capture events from window
	mlx_key_hook(env.mlx_win, keyboard_manage, &env);							//Capture events from keyboard
	mlx_mouse_hook(env.mlx_win, mouse_manage, &env);							//Capture events from the mouse
	mlx_loop(env.mlx);
	mlx_destroy_display(env.mlx);												//May not be present as a function in other libraries (e.g. for iOS)
	free(env.mlx_win);
	free(env.mlx);
	return (0);
}

/*
argc: Size of argv array
argv: Array of strings
e: Structure with all the data
Return the state 0 if all went well, 1 otherwise.
Initializes the data structure based on the input
data and returns an error if the parameters have
not been specified correctly.
*/
static int	parser(int argc, char *argv[], t_env *e)
{
	if (argc == 1 || argc > 4
		|| (argc == 2 && ft_strncmp(argv[1], "mandelbrot\0", 11) && ft_strncmp(argv[1], "ship\0", 5) && ft_strncmp(argv[1], "newton\0", 7))		//With 2 there can only be Mandelbrot or Ship or Newton
		|| (argc == 3)		//Can't be only 3
		|| (argc == 4 && !ft_strncmp(argv[1], "mandelbrot\0", 11))		//With 4 Mandelbrot is not good but only Julia
		|| (argc == 4 && !ft_strncmp(argv[1], "julia\0", 6) && (atod(argv[2]) == 0 || atod(argv[3]) == 0))		//Julia but must have two arguments which are numbers
	)
		return (1);
	if (!ft_strncmp(argv[1], "mandelbrot", 10))
	{
		e->ft_fractal = &ft_mandelbrot;
		e->area.fixed.re = 0.0;
		e->area.fixed.im = 0.0;
	}
	if (!ft_strncmp(argv[1], "julia", 5))
	{
		e->ft_fractal = &ft_julia;
		e->area.fixed.re = atod(argv[2]);
		e->area.fixed.im = atod(argv[3]);
	}
	if (!ft_strncmp(argv[1], "ship", 10))
	{
		e->ft_fractal = &ft_burning_ship;
		e->area.fixed.re = 0.0;
		e->area.fixed.im = 0.0;
	}
	if (!ft_strncmp(argv[1], "newton", 10))
	{
		e->ft_fractal = &ft_newton;
	}
	return (0);
}

/*
prog: The name of the running program
Return none.
Prints the usage of the program.
*/
static void	usage(char *prog)
{
	ft_putstr_fd("Usage: ", out);
	ft_putstr_fd(prog, out);
	ft_putstr_fd(" name_set [factor1] [factor2]\n\n", out);
	ft_putstr_fd(" Name set available:\n", out);
	ft_putstr_fd("  - mandelbrot\n", out);
	ft_putstr_fd("  - julia\n", out);
	ft_putstr_fd("  - newton\n", out);
	ft_putstr_fd("  - ship\n\n", out);
	ft_putstr_fd(" Example:\n", out);
	ft_putstr_fd("  ", out);
	ft_putstr_fd(prog, out);
	ft_putstr_fd(" mandelbrot\n", out);
	ft_putstr_fd("  ", out);
	ft_putstr_fd(prog, out);
	ft_putstr_fd(" julia <double> <double>\n", out);
	ft_putstr_fd("  ", out);
	ft_putstr_fd(prog, out);
	ft_putstr_fd(" newton\n", out);
	ft_putstr_fd("  ", out);
	ft_putstr_fd(prog, out);
	ft_putstr_fd(" ship\n\n", out);
	ft_putstr_fd(" Recommended:\n", out);
	ft_putstr_fd("  julia with c = 0.285 + 0.01 i\n", out);
	ft_putstr_fd("  julia with c = -0.835 - 0.222 i\n", out);
}
