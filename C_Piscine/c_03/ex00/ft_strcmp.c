/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:30:16 by ecoli             #+#    #+#             */
/*   Updated: 2021/12/08 11:18:57 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2)
{
	int	diff;

	diff = *(unsigned char *) s1 - *(unsigned char *) s2;
	while (!diff && *s2)
	{
		++s1;
		++s2;
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
