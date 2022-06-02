/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:52:58 by ecoli             #+#    #+#             */
/*   Updated: 2021/12/09 10:54:08 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (*to_find == '\0')
		return (str);
	while (1)
	{
		if (to_find[j] == '\0')
			return (&str[i - j]);
		if (str[i] == to_find[j])
			j++;
		else
			j = 0;
		if (str[i] == '\0')
			break ;
		i++;
	}
	return (0);
}
