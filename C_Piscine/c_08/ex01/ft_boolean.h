/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_boolean.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 12:52:28 by ecoli             #+#    #+#             */
/*   Updated: 2022/04/25 21:36:00 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BOOLEAN_H
# define FT_BOOLEAN_H

# include <unistd.h>

typedef enum e_bool
{
	false,
	true,
}	t_bool;

# define FALSE false;
# define TRUE true;

# define EVEN(n) (n % 2 == 0)

# define EVEN_MSG "I have an even number of arguments."
# define ODD_MSG "I have an odd number of arguments."

# define SUCCESS 0

#endif