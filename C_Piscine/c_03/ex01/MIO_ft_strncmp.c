/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:42:23 by ecoli             #+#    #+#             */
/*   Updated: 2021/12/09 10:42:57 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;
	int				diff;

	i = 0;
	diff = *(unsigned char *) s1 - *(unsigned char *) s2;
	while (i < n && !diff && *s2 && *s1)
	{
		++s1;
		++s2;
		i++;
		diff = *(unsigned char *) s1 - *(unsigned char *) s2;
	}
	if (diff < 0)
	{
		return (-1);
	}
	else if (diff > 0)
	{
		return (1);
	}
	return (diff);
}
