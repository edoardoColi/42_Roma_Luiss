/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:15:39 by ecoli             #+#    #+#             */
/*   Updated: 2023/02/10 18:08:05 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>

enum e_bool {
	false,
	true,
};

enum e_io {
	in,
	out,
	err,
};

typedef struct s_command
{
	char	**args;
	char	**rdr_in;	// <
	char	**rdr_out;	// >
	char	**heredoc;	// <<
	char	**append;	// >>
	int		ret;		//return del comando
	int		err;		//errorno
}	t_command;

#endif
