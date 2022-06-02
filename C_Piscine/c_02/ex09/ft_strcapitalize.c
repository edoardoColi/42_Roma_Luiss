/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:31:32 by ecoli             #+#    #+#             */
/*   Updated: 2021/12/06 18:31:19 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strlowcase(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] < 'A' || str[i] > 'Z'))
		{
			str[i] = str[i] + 32;
		}
		i++;
	}
	return (str);
}

int	check(char *str, int i)
{
	if ((str[i] < '0' || str[i] > '9') && (str[i] < 'a' || str[i] > 'z'))
		return (1);
	else
		return (0);
}

char	*ft_strcapitalize(char *str)
{
	int	i;
	int	upper;

	i = 0;
	upper = 1;
	str = ft_strlowcase(str);
	while (str[i] != '\0')
	{
		if (!(str[i] < '0' || str[i] > '9') && upper)
			upper = 0;
		else if (!(str[i] < 'a' || str[i] > 'z') && upper)
		{
			str[i] = str[i] - 32;
			upper = 0;
		}
		else if (check(str, i))
			upper = 1;
		i++;
	}
	return (str);
}
