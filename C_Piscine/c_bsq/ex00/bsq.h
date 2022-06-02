/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:28:47 by ebondi            #+#    #+#             */
/*   Updated: 2022/04/05 12:12:55 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# define SIZE_1B	1

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

#endif
