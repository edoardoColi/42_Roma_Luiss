/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy_0 <eddy_0@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 14:11:17 by ecoli             #+#    #+#             */
/*   Updated: 2022/06/02 18:25:32 by eddy_0           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);
int		ft_init2(int l, int h);

void	ft_print(int x, int y, int x_max, int y_max)

{
	if (x == 0 && y == 0)											//angolo sx-sup
		ft_putchar ('/');
	else if (x == x_max && y == y_max)								//angolo dx-inf
		ft_putchar ('/');
	else if (x == x_max && y == 0)									//angolo dx-sup
		ft_putchar ('\\');
	else if (x == 0 && y == y_max)									//angolo sx-inf
		ft_putchar ('\\');
	else if ((y == 0 || y == y_max) && (x != 0 || x != x_max))		//bordi orizzontali
		ft_putchar ('*');
	else if ((x == 0 || x == x_max) && (y != 0 || y != y_max))		//bordi verticali
		ft_putchar('*');
	else if ((x != 0 || x != x_max) && (y != 0 || y != y_max))		//spazi centrali
		ft_putchar(' ');
}

int	ft_init(int l, int h)
{
	if (l < 0 || h < 0)
		return (1);
	else if (l == 1 && h == 1)
	{
		ft_putchar('/');
		ft_putchar('\n');
		return (1);
	}
	else if (h == 1)
	{
		ft_putchar('/');
		while (l > 2)
		{
			ft_putchar ('*');
			l--;
		}
		ft_putchar('\\');
		ft_putchar('\n');
		return (1);
	}
	else
		return (ft_init2 (l, h));
}

int	ft_init2(int l, int h)
	{
	if (l == 1)
	{
		ft_putchar('/');
		ft_putchar('\n');
		while (h > 2)
		{
			ft_putchar('*');
			ft_putchar('\n');
			h--;
		}
		ft_putchar('\\');
		ft_putchar('\n');
		return (1);
	}
	else
		return (0);
}

void	rush(int l, int h)
{
	int	i;
	int	j;

	if (ft_init (l, h) == 1)
		return ;
	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < l)
		{
			ft_print (j, i, l -1, h -1);
			j++;
		}
		ft_putchar ('\n');
		i++;
	}	
}
