/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 04:14:26 by eddy              #+#    #+#             */
/*   Updated: 2023/05/23 23:49:51 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "global.h"
#include "functions.h"

static int is_line_empty(char *line);

/*
*/
int	data_checker(int fd, t_scene *s)
{
	int		presence_bit[3] = {0, 0, 0};											//For object identifier A, C, L (in this order)
	char	*line;
	char	*word;
	char	*ptr[2];																//To remember the exit point of the 2 ft_strtok_and_trimm_spaces
	char	buffer[32768];															//Enough to hold the whole configuration file
	
	ft_memset(buffer, 0, 32768);
	if (read(fd, buffer, sizeof(buffer)) >= 0)
	{
		line = ft_strtok_and_trimm_spaces(buffer, "\n", &ptr[0]);
		while (line != NULL)
		{
			if (!is_line_empty(line))
			{
				word = ft_strtok_and_trimm_spaces(line, " ", &ptr[1]);
				while (word != NULL)
				{
					if (word[0] == 'A' && word[1] == '\0' && presence_bit[0] == 0)
					{
						if(fill_amb_light_scene(&s->head_list, ft_strtok_and_trimm_spaces(NULL, " ", &ptr[1]), ft_strtok_and_trimm_spaces(NULL, " ", &ptr[1])) || ft_strtok_and_trimm_spaces(NULL, " ", &ptr[1]) != NULL)
						{
							error_msg("Non-compliant parameters.");
							return (1);
						}
						presence_bit[0] = 1;
					}
					else if (word[0] == 'C' && word[1] == '\0' && presence_bit[1] == 0)
					{
						if(fill_cam_scene(&s->head_list, ft_strtok_and_trimm_spaces(NULL, " ", &ptr[1]), ft_strtok_and_trimm_spaces(NULL, " ", &ptr[1]), ft_strtok_and_trimm_spaces(NULL, " ", &ptr[1])) || ft_strtok_and_trimm_spaces(NULL, " ", &ptr[1]) != NULL)
						{
							error_msg("Non-compliant parameters.");
							return (1);
						}
						presence_bit[1] = 1;
					}
					else if (word[0] == 'L' && word[1] == '\0' && presence_bit[2] == 0)
					{
						if(fill_light_scene(&s->head_list, ft_strtok_and_trimm_spaces(NULL, " ", &ptr[1]), ft_strtok_and_trimm_spaces(NULL, " ", &ptr[1]), ft_strtok_and_trimm_spaces(NULL, " ", &ptr[1])) || ft_strtok_and_trimm_spaces(NULL, " ", &ptr[1]) != NULL)
						{
							error_msg("Non-compliant parameters.");
							return (1);
						}
						presence_bit[2] = 1;
					}
					else if (word[0] == 's' && word[1] == 'p' && word[2] == '\0')
					{
						if(fill_sphere_scene(&s->head_list, ft_strtok_and_trimm_spaces(NULL, " ", &ptr[1]), ft_strtok_and_trimm_spaces(NULL, " ", &ptr[1]), ft_strtok_and_trimm_spaces(NULL, " ", &ptr[1])) || ft_strtok_and_trimm_spaces(NULL, " ", &ptr[1]) != NULL)
						{
							error_msg("Non-compliant parameters.");
							return (1);
						}
					}
					else if (word[0] == 'p' && word[1] == 'l' && word[2] == '\0')
					{
						if(fill_plane_scene(&s->head_list, ft_strtok_and_trimm_spaces(NULL, " ", &ptr[1]), ft_strtok_and_trimm_spaces(NULL, " ", &ptr[1]), ft_strtok_and_trimm_spaces(NULL, " ", &ptr[1])) || ft_strtok_and_trimm_spaces(NULL, " ", &ptr[1]) != NULL)
						{
							error_msg("Non-compliant parameters.");
							return (1);
						}
					}
					else if (word[0] == 'c' && word[1] == 'y' && word[2] == '\0')
					{
						if(fill_cylinder_scene(&s->head_list, ft_strtok_and_trimm_spaces(NULL, " ", &ptr[1]), ft_strtok_and_trimm_spaces(NULL, " ", &ptr[1]), ft_strtok_and_trimm_spaces(NULL, " ", &ptr[1]), ft_strtok_and_trimm_spaces(NULL, " ", &ptr[1]), ft_strtok_and_trimm_spaces(NULL, " ", &ptr[1])) || ft_strtok_and_trimm_spaces(NULL, " ", &ptr[1]) != NULL)
						{
							error_msg("Non-compliant parameters.");
							return (1);
						}
					}
					else
					{
						printf("Error\nThis '%s' parameter does not exist or has already been entered.\n",word);
						return (1);
					}
					free (word);
					word = ft_strtok_and_trimm_spaces(NULL, " ", &ptr[1]);
				}
			}
			free (line);
			line = ft_strtok_and_trimm_spaces(NULL, "\n", &ptr[0]);
		}
	}
	else
	{
		error_msg("Can not read from the configuration file.");
		return (1);
	}
	if (!presence_bit[0] || !presence_bit[1] || !presence_bit[2])
	{
		error_msg("Missing parameters for: Ambient lightning or Camera or Light.");
		return (1);
	}
	return (0);
}

/*
*/
int	fill_amb_light_scene(t_obj **head, char* parameter2, char* parameter1)
{
	t_obj	*new_obj;
	t_obj	*current;
	char	*ptr;

	new_obj = malloc(sizeof(t_obj));
	if (!new_obj)
	{
		error_msg("Malloc fail.");
		exit(1);
	}
	if (allocate_obj(new_obj) != 1)
	{
		error_msg("Malloc fail.");
		free(new_obj);
		exit(1);
	}
	new_obj->identifier = "A";
	*new_obj->light_ratio = ft_atod(parameter1);
	if (!(*new_obj->light_ratio >= 0.0 && *new_obj->light_ratio <= 1.0))
		return (1);
	*new_obj->colorRGB[0] = ft_adhoc_atoi(ft_strtok_and_trimm_spaces(parameter2, ",", &ptr));
	*new_obj->colorRGB[1] = ft_adhoc_atoi(ft_strtok_and_trimm_spaces(NULL, ",", &ptr));
	*new_obj->colorRGB[2] = ft_adhoc_atoi(ft_strtok_and_trimm_spaces(NULL, ",", &ptr));
	if (!(*new_obj->colorRGB[0] >= 0 && *new_obj->colorRGB[0] <= 255 && *new_obj->colorRGB[1] >= 0 && *new_obj->colorRGB[1] <= 255 && *new_obj->colorRGB[2] >= 0 && *new_obj->colorRGB[2] <= 255))
		return (1);
	new_obj->next = NULL;
	if (*head == NULL)
		*head = new_obj;
	else
	{
		current = *head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = new_obj;
	}
	free (parameter1);
	free (parameter2);
	return (0);
}

/*
*/
int	fill_cam_scene(t_obj **head, char* parameter3, char* parameter2, char* parameter1)
{
	t_obj	*new_obj;
	t_obj	*current;
	char	*ptr;

	new_obj = malloc(sizeof(t_obj));
	if (!new_obj)
	{
		error_msg("Malloc fail.");
		exit(1);
	}
	if (allocate_obj(new_obj) != 1)
	{
		error_msg("Malloc fail.");
		free(new_obj);
		exit(1);
	}
	new_obj->identifier = "C";
	(*new_obj->mass_center).x = ft_adhoc_atod(ft_strtok_and_trimm_spaces(parameter1, ",", &ptr));
	(*new_obj->mass_center).y = ft_adhoc_atod(ft_strtok_and_trimm_spaces(NULL, ",", &ptr));
	(*new_obj->mass_center).z = ft_adhoc_atod(ft_strtok_and_trimm_spaces(NULL, ",", &ptr));
	(*new_obj->versor).x = ft_adhoc_atod(ft_strtok_and_trimm_spaces(parameter2, ",", &ptr));
	(*new_obj->versor).y = ft_adhoc_atod(ft_strtok_and_trimm_spaces(NULL, ",", &ptr));
	(*new_obj->versor).z = ft_adhoc_atod(ft_strtok_and_trimm_spaces(NULL, ",", &ptr));
	if (!((*new_obj->versor).x >= -1.0 && (*new_obj->versor).x <= 1.0 && (*new_obj->versor).y >= -1.0 && (*new_obj->versor).y <= 1.0 && (*new_obj->versor).z >= -1.0 && (*new_obj->versor).z <= 1.0))
		return (1);
	*new_obj->fov = ft_atod(parameter3);
	if (!(*new_obj->fov > 0.0 && *new_obj->fov < 180.0))
		return (1);
	new_obj->next = NULL;
	if (*head == NULL)
		*head = new_obj;
	else
	{
		current = *head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = new_obj;
	}
	free (parameter1);
	free (parameter2);
	free (parameter3);
	return (0);
}

/*
*/
int	fill_light_scene(t_obj **head, char* parameter3, char* parameter2, char* parameter1)
{
	t_obj	*new_obj;
	t_obj	*current;
	char	*ptr;

	new_obj = malloc(sizeof(t_obj));
	if (!new_obj)
	{
		error_msg("Malloc fail.");
		exit(1);
	}
	if (allocate_obj(new_obj) != 1)
	{
		error_msg("Malloc fail.");
		free(new_obj);
		exit(1);
	}
	new_obj->identifier = "L";
	(*new_obj->mass_center).x = ft_adhoc_atod(ft_strtok_and_trimm_spaces(parameter1, ",", &ptr));
	(*new_obj->mass_center).y = ft_adhoc_atod(ft_strtok_and_trimm_spaces(NULL, ",", &ptr));
	(*new_obj->mass_center).z = ft_adhoc_atod(ft_strtok_and_trimm_spaces(NULL, ",", &ptr));
	*new_obj->light_ratio = ft_atod(parameter2);
	if (!(*new_obj->light_ratio >= 0.0 && *new_obj->light_ratio <= 1.0))
		return (1);
	*new_obj->colorRGB[0] = ft_adhoc_atod(ft_strtok_and_trimm_spaces(parameter3, ",", &ptr));
	*new_obj->colorRGB[1] = ft_adhoc_atod(ft_strtok_and_trimm_spaces(NULL, ",", &ptr));
	*new_obj->colorRGB[2] = ft_adhoc_atod(ft_strtok_and_trimm_spaces(NULL, ",", &ptr));
	if (!(*new_obj->colorRGB[0] >= 0 && *new_obj->colorRGB[0] <= 255 && *new_obj->colorRGB[1] >= 0 && *new_obj->colorRGB[1] <= 255 && *new_obj->colorRGB[2] >= 0 && *new_obj->colorRGB[2] <= 255))
		return (1);
	new_obj->next = NULL;
	if (*head == NULL)
		*head = new_obj;
	else
	{
		current = *head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = new_obj;
	}
	free (parameter1);
	free (parameter2);
	free (parameter3);
	return (0);
}

/*
*/
int	fill_sphere_scene(t_obj **head, char* parameter3, char* parameter2, char* parameter1)
{
	t_obj	*new_obj;
	t_obj	*current;
	char	*ptr;

	new_obj = malloc(sizeof(t_obj));
	if (!new_obj)
	{
		error_msg("Malloc fail.");
		exit(1);
	}
	if (allocate_obj(new_obj) != 1)
	{
		error_msg("Malloc fail.");
		free(new_obj);
		exit(1);
	}
	new_obj->identifier = "sp";
	(*new_obj->mass_center).x = ft_adhoc_atod(ft_strtok_and_trimm_spaces(parameter1, ",", &ptr));
	(*new_obj->mass_center).y = ft_adhoc_atod(ft_strtok_and_trimm_spaces(NULL, ",", &ptr));
	(*new_obj->mass_center).z = ft_adhoc_atod(ft_strtok_and_trimm_spaces(NULL, ",", &ptr));
	*new_obj->radius = ft_atod(parameter2) / 2.0;
	if (!(*new_obj->radius > 0.0))
		return (1);
	*new_obj->colorRGB[0] = ft_adhoc_atod(ft_strtok_and_trimm_spaces(parameter3, ",", &ptr));
	*new_obj->colorRGB[1] = ft_adhoc_atod(ft_strtok_and_trimm_spaces(NULL, ",", &ptr));
	*new_obj->colorRGB[2] = ft_adhoc_atod(ft_strtok_and_trimm_spaces(NULL, ",", &ptr));
	if (!(*new_obj->colorRGB[0] >= 0 && *new_obj->colorRGB[0] <= 255 && *new_obj->colorRGB[1] >= 0 && *new_obj->colorRGB[1] <= 255 && *new_obj->colorRGB[2] >= 0 && *new_obj->colorRGB[2] <= 255))
		return (1);
	new_obj->next = NULL;
	if (*head == NULL)
		*head = new_obj;
	else
	{
		current = *head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = new_obj;
	}
	free (parameter1);
	free (parameter2);
	free (parameter3);
	return (0);
}

/*
*/
int	fill_plane_scene(t_obj **head, char* parameter3, char* parameter2, char* parameter1)
{
	t_obj	*new_obj;
	t_obj	*current;
	char	*ptr;

	new_obj = malloc(sizeof(t_obj));
	if (!new_obj)
	{
		error_msg("Malloc fail.");
		exit(1);
	}
	if (allocate_obj(new_obj) != 1)
	{
		error_msg("Malloc fail.");
		free(new_obj);
		exit(1);
	}
	new_obj->identifier = "pl";
	(*new_obj->mass_center).x = ft_adhoc_atod(ft_strtok_and_trimm_spaces(parameter1, ",", &ptr));
	(*new_obj->mass_center).y = ft_adhoc_atod(ft_strtok_and_trimm_spaces(NULL, ",", &ptr));
	(*new_obj->mass_center).z = ft_adhoc_atod(ft_strtok_and_trimm_spaces(NULL, ",", &ptr));
	(*new_obj->versor).x = ft_adhoc_atod(ft_strtok_and_trimm_spaces(parameter2, ",", &ptr));
	(*new_obj->versor).y = ft_adhoc_atod(ft_strtok_and_trimm_spaces(NULL, ",", &ptr));
	(*new_obj->versor).z = ft_adhoc_atod(ft_strtok_and_trimm_spaces(NULL, ",", &ptr));
	if (!((*new_obj->versor).x >= -1.0 && (*new_obj->versor).x <= 1.0 && (*new_obj->versor).y >= -1.0 && (*new_obj->versor).y <= 1.0 && (*new_obj->versor).z >= -1.0 && (*new_obj->versor).z <= 1.0))
		return (1);
	*new_obj->colorRGB[0] = ft_adhoc_atoi(ft_strtok_and_trimm_spaces(parameter3, ",", &ptr));
	*new_obj->colorRGB[1] = ft_adhoc_atoi(ft_strtok_and_trimm_spaces(NULL, ",", &ptr));
	*new_obj->colorRGB[2] = ft_adhoc_atoi(ft_strtok_and_trimm_spaces(NULL, ",", &ptr));
	if (!(*new_obj->colorRGB[0] >= 0 && *new_obj->colorRGB[0] <= 255 && *new_obj->colorRGB[1] >= 0 && *new_obj->colorRGB[1] <= 255 && *new_obj->colorRGB[2] >= 0 && *new_obj->colorRGB[2] <= 255))
		return (1);
	new_obj->next = NULL;
	if (*head == NULL)
		*head = new_obj;
	else
	{
		current = *head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = new_obj;
	}
	free (parameter1);
	free (parameter2);
	free (parameter3);
	return (0);
}

/*
*/
int	fill_cylinder_scene(t_obj **head, char* parameter5, char* parameter4, char* parameter3, char* parameter2, char* parameter1)
{
	t_obj	*new_obj;
	t_obj	*current;
	char	*ptr;

	new_obj = malloc(sizeof(t_obj));
	if (!new_obj)
	{
		error_msg("Malloc fail.");
		exit(1);
	}
	if (allocate_obj(new_obj) != 1)
	{
		error_msg("Malloc fail.");
		free(new_obj);
		exit(1);
	}
	new_obj->identifier = "cy";
	(*new_obj->mass_center).x = ft_adhoc_atod(ft_strtok_and_trimm_spaces(parameter1, ",", &ptr));
	(*new_obj->mass_center).y = ft_adhoc_atod(ft_strtok_and_trimm_spaces(NULL, ",", &ptr));
	(*new_obj->mass_center).z = ft_adhoc_atod(ft_strtok_and_trimm_spaces(NULL, ",", &ptr));
	(*new_obj->versor).x = ft_adhoc_atod(ft_strtok_and_trimm_spaces(parameter2, ",", &ptr));
	(*new_obj->versor).y = ft_adhoc_atod(ft_strtok_and_trimm_spaces(NULL, ",", &ptr));
	(*new_obj->versor).z = ft_adhoc_atod(ft_strtok_and_trimm_spaces(NULL, ",", &ptr));
	if (!((*new_obj->versor).x >= -1.0 && (*new_obj->versor).x <= 1.0 && (*new_obj->versor).y >= -1.0 && (*new_obj->versor).y <= 1.0 && (*new_obj->versor).z >= -1.0 && (*new_obj->versor).z <= 1.0))
		return (1);
	*new_obj->radius = ft_atod(parameter3) / 2.0;
	if (!(*new_obj->radius > 0.0))
		return (1);
	*new_obj->height = ft_atod(parameter4);
	if (!(*new_obj->height > 0.0))
		return (1);
	*new_obj->colorRGB[0] = ft_adhoc_atoi(ft_strtok_and_trimm_spaces(parameter5, ",", &ptr));
	*new_obj->colorRGB[1] = ft_adhoc_atoi(ft_strtok_and_trimm_spaces(NULL, ",", &ptr));
	*new_obj->colorRGB[2] = ft_adhoc_atoi(ft_strtok_and_trimm_spaces(NULL, ",", &ptr));
	if (!(*new_obj->colorRGB[0] >= 0 && *new_obj->colorRGB[0] <= 255 && *new_obj->colorRGB[1] >= 0 && *new_obj->colorRGB[1] <= 255 && *new_obj->colorRGB[2] >= 0 && *new_obj->colorRGB[2] <= 255))
		return (1);
	new_obj->next = NULL;
	if (*head == NULL)
		*head = new_obj;
	else
	{
		current = *head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = new_obj;
	}
	free (parameter1);
	free (parameter2);
	free (parameter3);
	free (parameter4);
	free (parameter5);
	return (0);
}

/*
*/
static int is_line_empty(char *line)
{
	int i;

	for (i = 0; line[i] != '\0'; i++) {
		if (!ft_isspace(line[i])) {
			return 0;
		}
	}
	return 1;
}
