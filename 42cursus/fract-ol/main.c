/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 04:14:26 by eddy              #+#    #+#             */
/*   Updated: 2023/01/02 04:15:45 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

/*
posso usare:
open		//
close		//
read		//
write		//
malloc		//
free		//
perror		//
strerror	//
exit		//
*/
int	main(int argc, char *argv[])	//parametri per i set di Julia e Mandelbrot, altri parametri per il rengering.
									//Se non viene messo niente/qualcosa sbagliato fai Usage con tutti i parametri
//hook per rotella del mouse e ESC tastiera
{
	void	*img;
	void	*mlx;

	mlx = mlx_init();
	img = mlx_new_image(mlx, 1920, 1080);

	img++;
	argc++;
	argv++;

	return (0);
}

