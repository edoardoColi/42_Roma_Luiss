/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 04:14:26 by eddy              #+#    #+#             */
/*   Updated: 2023/05/23 22:42:06 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

// /*
// My own function implementing the original one.
// For more use "man strncmp" 
// */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && (i < n - 1))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*
My own function implementing the original one.
For more use "man atoi" 
*/
int	ft_adhoc_atoi(char *str)
{
	int					i;
	int					s;
	unsigned int		ret;

	s = 1;
	i = 0;
	ret = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')	//Are the various types of spaces
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		ret = ret * 10 + (str[i] - 48);		//Subtracting the offset of 0, according to the asci table, we get the char as a number
		i++;
	}
	free(str);
	return (s * ret);
}

/*
My own function implementing the string to double conversion, maneging dots.
*/
double	ft_atod(const char *str)
{
	int		i;
	int		s;
	double	ret;
	double	power;

	s = 1;
	i = 0;
	ret = 0.0;
	power = 1.0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		ret = ret * 10 + (str[i] - 48);//Subtracting the offset of 0, according to the asci table, we get the char as a number
		i++;
	}
	if (str[i] == '\0')
		return (s * ret / power);
	if (str[i] != '.')
		return (0);
	else
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		ret = ret * 10 + (str[i] - 48);//Subtracting the offset of 0, according to the asci table, we get the char as a number
		power *= 10;
		i++;
	}
	return (s * ret / power);
}

/*
My own function implementing the string to double conversion, maneging dots.
*/
double	ft_adhoc_atod(char *str)
{
	int		i;
	int		s;
	double	ret;
	double	power;

	s = 1;
	i = 0;
	ret = 0.0;
	power = 1.0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		ret = ret * 10 + (str[i] - 48);//Subtracting the offset of 0, according to the asci table, we get the char as a number
		i++;
	}
	if (str[i] == '\0')
	{
		free(str);
		return (s * ret / power);
	}
	if (str[i] != '.')
	{
		free(str);
		return (0);
	}
	else
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
		{
			free(str);
			return (0);
		}
		ret = ret * 10 + (str[i] - 48);//Subtracting the offset of 0, according to the asci table, we get the char as a number
		power *= 10;
		i++;
	}
	free(str);
	return (s * ret / power);
}

/*
My own function implementing the original one.
For more use "man isdigit"
*/
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/*
My own function implementing the original one.
For more use "man strlen" 
*/
size_t	ft_strlen(const char *s)
{
	size_t	l;

	l = 0;
	while (s[l] != '\0')
		l++;
	return (l);
}

/*
c: The character to output.
fd: The file descriptor on which to write.
Return none.
Outputs the character ’c’ to the given file
descriptor.
*/
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/*
s: The string to output.
fd: The file descriptor on which to write.
Return none.
Outputs the string ’s’ to the given file
descriptor.
*/
void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
	}
}

/*
dst: Destination string
src: Source string
size: Maximum destination size
Return the total length of the string tried to create.
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = -1;
	while (++i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
	}
	dst[i] = '\0';
	while (src[i] != '\0')
	{
		i++;
	}
	return (i);
}

/*
My own function implementing the original one.
For more use "man memchr" 
*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		if (*ptr == (unsigned char) c)
			return ((void *)ptr);
		ptr++;
		i++;
	}
	return (NULL);
}

/*
My own function implementing the original one.
For more use "man strchr" 
*/
char	*ft_strchr(const char *s, int c)
{
	return (ft_memchr(s, c, ft_strlen(s) + 1));
}

/*
My own function implementing the original one.
For more use "man memset" 
*/
void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = c;
		i++;
	}
	return (b);
}

/*
c: Character
Returns the boolean value of the various logical operators.
Check if the character passed is a type ot space.
*/
int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

/*
str: String to parse
delim: Delimiters
saveptr: Pointer to tell where to start parse
Returns the next substring between the given delimiters, or NULL if something fail.
Copies the next substring delimited by the delimiter to a new string. Memory is allocated for the new string.
*/
char	*ft_strtok_and_trimm_spaces(char *str, const char *delim, char **saveptr)
{
	size_t	len;
	size_t	token_len;
	char	*next_delim;
	char	*result;
	char	*token;

	if (str == NULL)															//If `str` is NULL, continue parsing from the last saved position
		str = *saveptr;
	if (str == NULL || *str == '\0')
	{
		*saveptr = NULL;
		return (NULL);
	}
	next_delim = ft_strchr(str, *delim);										//Find the next delimiter in the string
	if (next_delim == NULL)														//If there are no more delimiters, return the remainder of the string
	{
		len = ft_strlen(str);
		result = malloc(len + 1);
		if (!result)
		{
			return (NULL);
		}
		ft_strlcpy(result, str, len + 1);
		*saveptr = NULL;
		return (result);
	}
	token_len = next_delim - str;
	token = malloc(token_len + 1);												//Allocate memory for the token and copy it
	if (!token)
	{
		return (NULL);
	}
	ft_strlcpy(token, str, token_len + 1);
	while(ft_isspace(next_delim[1]))													//Skip all space(s)
		*saveptr = next_delim++;												//Update the save pointer
	*saveptr = next_delim + 1;													//Update the save pointer and return the token	
	return (token);
}

/*
*/
double	dist_3d(t_3dp a, t_3dp b)
{
	double distance = sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2));
	return (distance);
}

/*
*/
t_3dp	calc_versor(t_3dp from, t_3dp to)
{
	t_3dp direction;
	direction.x = to.x - from.x;
	direction.y = to.y - from.y;
	direction.z = to.z - from.z;

	float length = sqrt(pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2));

	t_3dp normalizedDirection;
	normalizedDirection.x = direction.x / length;
	normalizedDirection.y = direction.y / length;
	normalizedDirection.z = direction.z / length;

	return normalizedDirection;
}

/*
*/
void	versor_to_matrix(float x, float y, float z, float matrix[3][3])
{
	float cos_t = cosf(M_PI_2);
	float sin_t = sinf(M_PI_2);
	float cos_t_1 = 1.0f - cos_t;
	float x_sin_t = x * sin_t;
	float y_sin_t = y * sin_t;
	float z_sin_t = z * sin_t;
	float x_cos_t_1 = x * cos_t_1;
	float y_cos_t_1 = y * cos_t_1;
	float z_cos_t_1 = z * cos_t_1;
	
	matrix[0][0] = cos_t + x * x_cos_t_1;
	matrix[0][1] = x * y_cos_t_1 - z_sin_t;
	matrix[0][2] = x * z_cos_t_1 + y_sin_t;
	matrix[1][0] = y * x_cos_t_1 + z_sin_t;
	matrix[1][1] = cos_t + y * y_cos_t_1;
	matrix[1][2] = y * z_cos_t_1 - x_sin_t;
	matrix[2][0] = z * x_cos_t_1 - y_sin_t;
	matrix[2][1] = z * y_cos_t_1 + x_sin_t;
	matrix[2][2] = cos_t + z * z_cos_t_1;
}

/*
*/
int	argb_to_int(t_3dp a, int r, int g, int b)
{
	r = (r * a.x) / 255;
	g = (g * a.y) / 255;
	b = (b * a.z) / 255;
	int color = (r << 16) | (g << 8) | b;
	return color;
}

/*
*/
int	allocate_obj(t_obj *obj)
{
	obj->colorRGB[0] = malloc(sizeof(int));
	obj->colorRGB[1] = malloc(sizeof(int));
	obj->colorRGB[2] = malloc(sizeof(int));
	obj->mass_center = malloc(sizeof(t_3dp));
	obj->versor = malloc(sizeof(t_3dp));
	obj->fov = malloc(sizeof(double));
	obj->height = malloc(sizeof(double));
	obj->radius = malloc(sizeof(double));
	obj->light_ratio = malloc(sizeof(double));
	if (!obj->colorRGB || !obj->colorRGB || !obj->colorRGB || !obj->mass_center || !obj->versor || !obj->fov || !obj->height || !obj->radius || !obj->light_ratio)
		return (0);
	return (1);
}

/*
*/
void	free_list(t_scene *s)
{
	t_obj *obj;
	t_obj *next;

	obj = s->head_list;
	next = obj->next;
	while (obj != NULL)
	{
		next = obj->next;
		deallocate_obj(obj);
		obj = next;
	}
}

/*
*/
void	deallocate_obj(t_obj *obj)
{
	if (obj->colorRGB[0])
		free(obj->colorRGB[0]);
	if (obj->colorRGB[1])
		free(obj->colorRGB[1]);
	if (obj->colorRGB[2])
		free(obj->colorRGB[2]);
	if (obj->mass_center)
		free(obj->mass_center);
	if (obj->versor)
		free(obj->versor);
	if (obj->fov)
		free(obj->fov);
	if (obj->height)
		free(obj->height);
	if (obj->radius)
		free(obj->radius);
	if (obj->light_ratio)
		free(obj->light_ratio);
	free(obj);
}

/*
*/
void	debug_list_print(t_scene *s)
{
	t_obj	*head;

	head = s->head_list;
	while (head != NULL)
	{
		printf("==========================================================\n");
		printf("identifier:      %s\n", head->identifier ? head->identifier : "NULL");
		printf("colorRGB:        %d, %d, %d\n",
			head->colorRGB[0] ? *head->colorRGB[0] : 0,
			head->colorRGB[1] ? *head->colorRGB[1] : 0,
			head->colorRGB[2] ? *head->colorRGB[2] : 0);
		printf("mass_center:     %f, %f, %f\n",
			head->mass_center ? head->mass_center->x : 0.0,
			head->mass_center ? head->mass_center->y : 0.0,
			head->mass_center ? head->mass_center->z : 0.0);
		printf("fov:             %f\n", head->fov ? *head->fov : 0.0);
		printf("height:          %f\n", head->height ? *head->height : 0.0);
		printf("radius:          %f\n", head->radius ? *head->radius : 0.0);
		printf("light_ratio:     %f\n", head->light_ratio ? *head->light_ratio : 0.0);
		printf("versor:          %f, %f, %f\n",
			head->versor ? head->versor->x : 0.0,
			head->versor ? head->versor->y : 0.0,
			head->versor ? head->versor->z : 0.0);
		printf("NEXT:            %s\n", head->next ? "->" : "><");
		head = head->next;
	}
	printf("==========================================================\n");
}
