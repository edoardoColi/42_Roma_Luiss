/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:15:39 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/01 01:10:53 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>

# define MAX_ENTRY	128
# define MAX_NAME	4096
# define MAX_CMD	3072

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
	char	**rin_and_heredoc;			//Store < e <<
	char	**rout_and_append;			//Store > e >>
	int		redin_type[MAX_ENTRY];		//MOD per ricordare quale append a quale override
	int		redout_type[MAX_ENTRY];		//MOD per ricordare quale file e quale heredoc
	int		fd[2];						//File descriptors for pipe
}	t_command;

#endif
