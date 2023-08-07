/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 04:14:26 by eddy              #+#    #+#             */
/*   Updated: 2023/05/23 22:20:01 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "global.h"
#include "functions.h"

static int	parser(char *file, t_scene *s);

/*
*/
int	main(int argc, char *argv[])
{
	t_scene	scene;																//Contains all the information

	if (argc == 1)
	{
		error_msg("A scene configuration file with '.rt' extension must be provided as first parameter.");
		return (1);
	}
	scene.head_list = NULL;
	if (parser(argv[1], &scene))
		return (1);
	debug_list_print(&scene);
	printf("Welcome. Stay ready to discover...\n");
	scene.mlx = mlx_init();
	scene.mlx_win = mlx_new_window(scene.mlx, WIDTH, HEIGHT, "miniRT\t\tby 42TEAM");
	scene.img.image = mlx_new_image(scene.mlx, WIDTH, HEIGHT);
	scene.img.data = mlx_get_data_addr(scene.img.image, &scene.img.bpp, &scene.img.size_line, &scene.img.type);
	ft_mlx_draw(&scene);
	mlx_hook(scene.mlx_win, 17, 0, window_cross, &scene);						//Capture events from window
	mlx_key_hook(scene.mlx_win, keyboard_manage, &scene);						//Capture events from keyboard
	mlx_mouse_hook(scene.mlx_win, mouse_manage, &scene);						//Capture events from the mouse
	mlx_loop(scene.mlx);
	mlx_destroy_display(scene.mlx);												//May not be present as a function in other libraries (e.g. for iOS)
	free(scene.mlx_win);
	free(scene.mlx);
	return (0);
}

/*
file: Filename of configuration file
s: Structure for the data
Return the state 0 if all went well, 1 otherwise.
Initializes the data structure based on the input
data and returns an error if the parameters have
not been specified correctly.
*/
static int	parser(char *file, t_scene *s)
{
	int		fd;
	int		length;
	int		ret;
	
	length = ft_strlen(file);
	if(length > 3 && file[length-3] == '.' && file[length-2] == 'r' && file[length-1] == 't')
	{
		fd = open(file, O_RDONLY);
		if (fd < 0)
		{
			error_msg("Unable to open the configuration file.");
			return (1);
		}
	}
	else
	{
		error_msg("The scene configuration must have '.rt' extension.");
		return (1);
	}
	ret = 0;
	if (data_checker(fd, s))
		ret = 1;
	close(fd);
	return (ret);
}

/*
error: The type of the error
Return none.
Prints "Error" followed by the verbose explanation.
*/
void	error_msg(char *error)
{
	printf("Error\n%s\n",error);
}
