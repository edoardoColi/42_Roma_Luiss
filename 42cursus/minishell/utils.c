/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by eddy              #+#    #+#             */
/*   Updated: 2023/04/01 01:29:16 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

extern int	g_toknow[2];

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
name: Name of the environment variable
env: Reference to the environment used
Return the value of the environment variable,or NULL;
Extracts the indicated one from the list of environment variables.
*/
char	*adhoc_getenv(const char *name, char *env[])
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
		{
			return (&(env[i][len + 1]));
		}
		i++;
	}
	return (NULL);
}

/*
name: Name of the environment variable
value: String to put in environment variable
env: Reference to the environment used
Return 0.
Modifies the specified environment variable by changing it
to value, if it doesn't exist is added to the list of environment variable. 
*/
int	adhoc_setenv(const char *name, char *value, char *env[])
{
	int		i;
	int		j;
	int		pos;
	int		len;
	char	tmp[MAX_NAME];

	pos = -1;
	len = ft_strlen(name);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
		{
			pos = i;
			break ;
		}
		i++;
	}
	if (pos == -1)																//If the environment variable is not present
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
		free(env[pos]);
		env[pos] = ft_strdup(tmp);												//Internally uses a malloc
		env[pos + 1] = NULL;
	}
	else																		//If the environment variable is not present
	{
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
dst: Destination string
src: Character
Return the new dimension of the destination string.
Concatenates a character to the target string.
*/
size_t	ft_charcat(char *dst, const char src)
{
	size_t	dst_len;

	dst_len = ft_strlen(dst);
	dst[dst_len] = src;
	dst[dst_len + 1] = '\0';
	return (dst_len + 1);
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
c: Character
Returns the boolean value of the various logical operators.
Check if the character passed is a letter or a number.
*/
int	adhoc_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'));
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
str: Text string
Return a string.
Duplicate of the passed string allocating new memory up to MAX_NAME
*/
char	*ft_strdup(char *str)
{
	int		i;
	char	*copy;

	copy = (char *) malloc(sizeof(char) * MAX_NAME);
	if (!copy)
	{
		perror("Fail malloc\n");
		return (NULL);
	}
	i = 0;
	while (str[i] != '\0' && i < MAX_NAME - 1)
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

/*
n: the integer to convert.
Return the string representing the integer.
NULL if the allocation fails.
Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
Negative numbers must be handled.
*/
char	*ft_itoa(int n)
{
	char	*str;											//Return value
	size_t	len;											//Size of the number as a string
	long	n_long;											//We use long to implicitly manage the INT_MIN value

	n_long = (long) n;
	len = size_num(n_long);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (n_long == 0)
		str[0] = '0';
	if (n_long < 0)
	{
		str[0] = '-';
		n_long = n_long * -1;
	}
	while (n_long > 0)
	{
		str[len] = (n_long % 10) + '0';						//Adding the offset of 0, according to the asci table, we get the number as a char
		n_long = n_long / 10;
		len--;
	}
	return (str);
}

/*
n: the integer to convert.
Return the integer.
Count and return the size of the number in order to become a char.
*/
size_t	size_num(int n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

/*
str: String to parse
delim: Delimiters
saveptr: Pointer to tell where to start parse
Returns the next substring between the given delimiters, or NULL if something fail.
Copies the next substring delimited by the delimiter to a new string. Memory is allocated for the new string.
*/
char	*ft_strtok(char *str, const char *delim, char **saveptr)
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
	*saveptr = next_delim + 1;													//Update the save pointer and return the token
	return (token);
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
For more use "man strchr" 
*/
char	*ft_strchr(const char *str, int c)
{
	while (*str != '\0')														// Search for the character in the string
	{
		if (*str == c)
		{
			return ((char *)str);
		}
		str++;
	}
	if (c == '\0')																//Check if the character is the null terminator
	{
		return ((char *)str);
	}
	return (NULL);																//Character not found
}

/*
str: Text string
env: Reference to the environment used
Return none.
Change the string parts starting with $ ​​as determined by the dictionary of which the environment env.
*/
void	dollar_replace(char *str, char *env[])
{
	int		j;
	int		flag;
	int		quote;
	char	env_var[MAX_NAME];
	char	new_cmd[MAX_NAME];

	ft_memset(new_cmd, '\0', MAX_NAME);											//Clean up before copying over
	ft_memset(env_var, '\0', MAX_NAME);											//Clean up before copying over
	j = -1;
	flag = 0;
	quote = 0;
	while (str[++j] != '\0')
	{
		if (str[j] == '\'')
			quote++;
		if (quote % 2 == 0)
		{
			if (str[j] == '$')
			{
				j++;
				while ((adhoc_isalpha(str[j]) || str[j] == '?') && str[j] != '\0')
				{
					if (flag == 0)
						flag = 1;
					if (str[j] == '?' && env_var[0] == '\0')
					{
						ft_charcat(env_var, str[j]);
						break ;
					}
					else if (str[j] == '?')
						break ;
					else
						ft_charcat(env_var, str[j]);
					j++;
				}
				if (flag == 1)
				{
					if (env_var[0] == '?')
					{
						ft_strlcat(new_cmd, ft_itoa(g_toknow[0]), MAX_NAME);
						j++;
					}
					else if (adhoc_getenv(env_var, env))
						ft_strlcat(new_cmd, adhoc_getenv(env_var, env), MAX_NAME);
					flag = 0;
					ft_memset(env_var, '\0', MAX_NAME);							//Clean up before using again
				}
			}
			if (str[j] == '$')
				j--;
			else
				ft_charcat(new_cmd, str[j]);
		}
		else
			ft_charcat(new_cmd, str[j]);
	}
	ft_memset(str, '\0', MAX_NAME);												//Clean up before copying over
	ft_strlcat(str, new_cmd, MAX_NAME);
}

/*
My own function implementing the original one.
For more use "man atoi" 
*/
int	ft_atoi(const char *str)
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
		ret = ret * 10 + (str[i] - 48);							//Subtracting the offset of 0, according to the asci table, we get the char as a number
		i++;
	}
	return (s * ret);
}

/*
My own function implementing the original one.
For more use "man isdigit" 
*/
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
