/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 04:14:26 by eddy              #+#    #+#             */
/*   Updated: 2023/05/24 00:03:25 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

/*
scene: Structure with all the data
Return none.
Calculates the color of each pixel and then represents it in the window.
*/
void	ft_mlx_draw(t_scene *scene)
{
	int		x;
	int		y;

	x = -1;
	y = -1;
	mlx_clear_window(scene->mlx, scene->mlx_win);

////////////////////TODO riscrivere e inserire in una funzione per il step H e W
	double halfWidth = (WIDTH / 2.0) / RATIO;
	double halfHeigth = (HEIGHT / 2.0) / RATIO;

	scene->dist_viewport = halfWidth / tan(( *(scene->head_list->next->fov) / 2.0) * (MY_PI / 180.0));
	printf("\nSono in (%f, %f, %f)\n",scene->head_list->next->mass_center->x,scene->head_list->next->mass_center->y, scene->head_list->next->mass_center->z);
	printf("ho %f distanza\n",scene->dist_viewport);
	printf("quindi guardo oltre il punto (%f, %f, %f)\n",scene->head_list->next->mass_center->x + scene->head_list->next->versor->x * scene->dist_viewport,   scene->head_list->next->mass_center->y + scene->head_list->next->versor->y * scene->dist_viewport,   scene->head_list->next->mass_center->z + scene->head_list->next->versor->z * scene->dist_viewport);
	t_3dp center;
	center.x = scene->head_list->next->mass_center->x + scene->head_list->next->versor->x * scene->dist_viewport;
	center.y = scene->head_list->next->mass_center->y + scene->head_list->next->versor->y * scene->dist_viewport;
	center.z = scene->head_list->next->mass_center->z + scene->head_list->next->versor->z * scene->dist_viewport;

	t_3dp look;
	look.x = scene->head_list->next->versor->x;
	look.y = scene->head_list->next->versor->y;
	look.z = scene->head_list->next->versor->z;
	
	t_3dp right;//TODO fai matrice di torazione e applica agli oggette, anche la traslazione... Magari nella stessa matrice
	right.x = 0.0;//-(look.z);
	right.y = 0.0;//0.0;
	right.z = -1.0;//look.x;

	t_3dp up;
	up.x =  0.0;//look.y * right.z - look.z * right.y;
	up.y =  -1.0;//-(look.z * right.x - look.x * right.z);
	up.z =  0.0;//look.x * right.y - look.y * right.x;

	t_3dp up_sideA;
	up_sideA.x = (center.x + halfWidth * right.x) + halfHeigth * up.x;
	up_sideA.y = (center.y + halfWidth * right.y) + halfHeigth * up.y;
	up_sideA.z = (center.z + halfWidth * right.z) + halfHeigth * up.z;

	t_3dp down_sideA;
	down_sideA.x = (center.x + halfWidth * right.x) + halfHeigth * -up.x;
	down_sideA.y = (center.y + halfWidth * right.y) + halfHeigth * -up.y;
	down_sideA.z = (center.z + halfWidth * right.z) + halfHeigth * -up.z;

	t_3dp up_sideB;
	up_sideB.x = (center.x + halfWidth * -right.x) + halfHeigth * up.x;
	up_sideB.y = (center.y + halfWidth * -right.y) + halfHeigth * up.y;
	up_sideB.z = (center.z + halfWidth * -right.z) + halfHeigth * up.z;

	printf("quindi guardo look (%f, %f, %f)\n",look.x,look.y,look.z);
	printf("quindi guardo right (%f, %f, %f)\n",right.x,right.y,right.z);
	printf("quindi guardo up (%f, %f, %f)\n",up.x,up.y,up.z);
	printf("\nquindi tl (%f, %f, %f)\n",up_sideB.x,up_sideB.y,up_sideB.z);
	printf("quindi tr (%f, %f, %f)\n",up_sideA.x,up_sideA.y,up_sideA.z);
	printf("quindi br (%f, %f, %f)\n",down_sideA.x,down_sideA.y,down_sideA.z);

	printf("distanza top %f quindi passo %f\n",dist_3d(up_sideA, up_sideB),dist_3d(up_sideA, up_sideB)/WIDTH);
	printf("distanza side %f quindi passo %f\n",dist_3d(up_sideA, down_sideA),dist_3d(up_sideA, down_sideA)/HEIGHT);

	t_3dp tmp;
	tmp.x = up_sideB.x;
	tmp.y = up_sideB.y;
	tmp.z = up_sideB.z;

	double step_H = dist_3d(up_sideA, down_sideA) / HEIGHT;
	double step_W = dist_3d(up_sideA, up_sideB) / WIDTH;
	int color;
//////////TODO leve printf
	while (++x < WIDTH)
	{
		tmp.x = tmp.x + step_W * x * -up.x;
		tmp.y = tmp.y + step_W * x * -up.y;
		tmp.z = tmp.z + step_W * x * -up.z;
		while (++y < HEIGHT)
		{
			// printf("retta             camera->(%f, %f, %f)	per pixel (%d,%d) 	con versore (%f, %f, %f)\n",tmp.x,tmp.y,tmp.z,x,y,calc_versor(*(scene->head_list->next->mass_center), tmp).x, calc_versor(*(scene->head_list->next->mass_center), tmp).y, calc_versor(*(scene->head_list->next->mass_center), tmp).z);
			color = color_from_intersez(&scene->head_list, tmp, calc_versor(*(scene->head_list->next->mass_center), tmp));
			my_mlx_pixel_put(&scene->img, x, y, color);
			tmp.x = tmp.x + step_H * right.x;
			tmp.y = tmp.y + step_H * right.y;
			tmp.z = tmp.z + step_H * right.z;
		}
		y = -1;
		tmp.x = up_sideB.x;
		tmp.y = up_sideB.y;
		tmp.z = up_sideB.z;
	}
	my_mlx_pixel_put(&scene->img, WIDTH / 2, HEIGHT / 2, argb_to_int((t_3dp){255,255,255}, 255, 0, 0));				//Color the central pixel of the window red(255,0,0)(0x00FF0000)
	mlx_put_image_to_window(scene->mlx, scene->mlx_win, scene->img.image, 0, 0);
}

/*
*/
int	color_from_intersez(t_obj **head, t_3dp line_point, t_3dp line_versor)
{
	int		inter_flag;
	int		color[3];
	double	point_intersez[3];
	double	fog = 1000000.0;
	double	tmp = fog;
	double	dist_min = fog;	//tipo il FOG
	t_obj	*ref_o;
	t_3dp	plane_point;
	t_3dp	plane_versor;
	t_3dp	spere_point;
	double	spere_radius;

	inter_flag = 0;
	ref_o = *head;
	while (ref_o != NULL)
	{
		if ((*ref_o).identifier[0] == 'p' && (*ref_o).identifier[1] == 'l' && (*ref_o).identifier[2] == '\0')
		{
			plane_point = *ref_o->mass_center;
			plane_versor = *ref_o->versor;
			tmp = -((plane_versor.x * (line_point.x - plane_point.x) + plane_versor.y * (line_point.y - plane_point.y) + plane_versor.z * (line_point.z - plane_point.z)) / (plane_versor.x * line_versor.x + plane_versor.y * line_versor.y + plane_versor.z * line_versor.z));	//TODO devo controllare che non sto dividendo per zero
			if (0 < tmp && tmp <= dist_min)
			{
				if (inter_flag == 0)
					inter_flag = 1;
				dist_min = tmp;
				color[0] = *ref_o->colorRGB[0];
				color[1] = *ref_o->colorRGB[1];
				color[2] = *ref_o->colorRGB[2];
				point_intersez[0] = plane_point.x + plane_versor.x * tmp;
				point_intersez[1] = plane_point.y + plane_versor.y * tmp;
				point_intersez[2] = plane_point.z + plane_versor.z * tmp;
				// printf("punto di intersezione->(%f, %f, %f) di colore (%i, %i, %i)\n",point_intersez[0],point_intersez[1],point_intersez[2],color[0],color[1],color[2]);
				if (tmp == 0)
				{
					color[0] = 225;
					color[1] = 225;
					color[2] = 225;
				}
			}
		}
		if ((*ref_o).identifier[0] == 's' && (*ref_o).identifier[1] == 'p' && (*ref_o).identifier[2] == '\0')
		{
			spere_point = *ref_o->mass_center;
			spere_radius = *ref_o->radius;
			
			double par_A = pow(line_versor.x,2.0) + pow(line_versor.y,2.0) + pow(line_versor.z,2.0);
			double par_B = 2.0*( (line_point.x - spere_point.x) * line_versor.x + (line_point.y - spere_point.y) * line_versor.y + (line_point.z - spere_point.z) * line_versor.z );
			double par_C = pow((line_point.x - spere_point.x),2.0) + pow((line_point.y - spere_point.y),2.0) + pow((line_point.z - spere_point.z),2.0) - pow(spere_radius,2.0);
			if(pow(par_B,2.0) -( 4 * par_A * par_C) >= 0) {
				tmp = (-par_B - sqrt(pow(par_B,2.0) - ( 4 * par_A * par_C))) / (2.0 * par_A);//TODO controllo della radice 
				if (0 < tmp && tmp <= dist_min)
				{
					if (inter_flag == 0)
						inter_flag = 1;
					dist_min = tmp;
					color[0] = *ref_o->colorRGB[0];
					color[1] = *ref_o->colorRGB[1];
					color[2] = *ref_o->colorRGB[2];
					point_intersez[0] = plane_point.x + plane_versor.x * tmp;
					point_intersez[1] = plane_point.y + plane_versor.y * tmp;
					point_intersez[2] = plane_point.z + plane_versor.z * tmp;
					// printf("punto di intersezione->(%f, %f, %f) di colore (%i, %i, %i)\n",point_intersez[0],point_intersez[1],point_intersez[2],color[0],color[1],color[2]);
					if (tmp == 0)
					{
						color[0] = 225;
						color[1] = 225;
						color[2] = 225;
					}
				}
			}
		}
		if ((*ref_o).identifier[0] == 'c' && (*ref_o).identifier[1] == 'y' && (*ref_o).identifier[2] == '\0')
		{
			//TODO
		}
		tmp = fog;
		ref_o = (*ref_o).next;
	}
	if (inter_flag == 1)
	{
		// printf("Trovata intersezione vicina con %d,%d,%d colori\n\n",color[0],color[1],color[2]);
		t_3dp ambient=light_tracing(head, point_intersez[0],point_intersez[1],point_intersez[2]);
		return (argb_to_int(ambient,color[0],color[1],color[2]));
	}
	else
	{
		// printf("No intersez \n\n");
		return (argb_to_int((t_3dp){255,255,255},255,255,255));
	}
}

/*
*/
t_3dp	light_tracing(t_obj **head, double p_x, double p_y, double p_z){
	t_3dp sum_light;

	sum_light.x=255;//TODO prendere valori da luci ecc.
	sum_light.y=255;
	sum_light.z=255;

	return sum_light;
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
