/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by eddy              #+#    #+#             */
/*   Updated: 2023/03/12 21:38:58 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

/*
*/
int	ft_isspace(char c)
{
		if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
			return (1);
		return (0);
}

/*
*/
char	*adhoc_getenv(const char *name, char *env[])
{
	int	i;
	int	len;
	len = ft_strlen(name);
	i = 0;
	while (env[i] != NULL) {
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
		{
			return (&(env[i][len+1]));
		}
		i++;
	}
	return (NULL);
}

/*
*/
int	adhoc_setenv(const char *name, char *value, char *env[])
{
	int	i;
	int	j;
	int	pos;
	int	len;
	char tmp[MAX_NAME];

	pos = -1;
	len = ft_strlen(name);
	i = 0;
	while (env[i] != NULL) {
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
		{
			pos = i;
			break;
		}
		i++;
	}
	if (pos == -1)//se la variabile d'ambiente non e' presente
	{
		pos = i;
		i = 0;
		j = 0;
		while (name[j] != '\0')
		{
			tmp[i] = name[j];
			j++;
			i++;
		}
		tmp[i] = '=';
		i++;
		j = 0;
		while (value[j] != '\0')
		{
			tmp[i] = value[j];
			j++;
			i++;
		}
		tmp[i] = '\0';
		env[pos] = ft_strdup(tmp);//internamente usa una malloc
		env[pos + 1] = NULL;
	}
	else{//se la variabile d'ambiente e' presente
		i = 0;
		j = 0;
		while (name[j] != '\0')
		{
			env[pos][i] = name[j];
			j++;
			i++;
		}
		env[pos][i] = '=';
		i++;
		j = 0;
		while (value[j] != '\0')
		{
			env[pos][i] = value[j];
			j++;
			i++;
		}
		env[pos][i] = '\0';
	}
	return (0);
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
My own function implementing the original one.
For more use "man strlcat" 
*/
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize > 0 && dst_len < dstsize - 1)
	{
		while ((i + dst_len + 1) < dstsize && src[i] != '\0')	//Look carefully at the man
		{
			dst[dst_len + i] = src[i];
			i++;
		}
		dst[dst_len + i] = '\0';
	}
	if (dst_len >= dstsize)
		dst_len = dstsize;
	return (dst_len + src_len);
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
My own function implementing the original one.
For more use "man strncmp" 
*/
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
*/
char	*ft_strdup(char *str)
{
	int		i;
	char	*copy;

	copy = (char*) malloc( sizeof(char) *MAX_NAME);//TODO controlla return
	if (!copy)
	{
		perror("Fail malloc\n");
		return (NULL);
	}
	i = 0;
	while (str[i] != '\0' && i < MAX_NAME - 1) {
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
