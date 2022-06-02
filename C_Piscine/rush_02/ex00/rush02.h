/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush02.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 17:09:22 by ecoli             #+#    #+#             */
/*   Updated: 2021/12/12 17:15:33 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSH02_H
# define RUSH02_H

# define    SIZE_1B    1

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

enum e_bool {
	false,
	true,
};

enum e_io {
	in,
	out,
	err,
};

typedef struct s_list{
	int				valore;
	int				decine;
	char			*nome;
	struct s_list	*next;
}	t_nodo;

#endif
