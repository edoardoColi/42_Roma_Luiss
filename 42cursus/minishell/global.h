/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:15:39 by ecoli             #+#    #+#             */
/*   Updated: 2023/02/13 20:10:57 by ecoli            ###   ########.fr       */
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
	char	args[2048][2048];
	char	rdr_in[2048][2048];		// <
	char	rdr_out[2048][2048];	// >
	char	heredoc[2048][2048];	// <<
	char	append[2048][2048];		// >>
	int		ret;		//return del comando
	int		err;		//errorno
}	t_command;

#endif
