/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:54:45 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:22:56 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "glob.h"

static void	print_free_close(char *str, int fd, DIR *dir, int err)
{
	set_ecode(err);
	ft_printf("%s\n", str, err);
	if (fd != -1)
		close(fd);
	if (dir)
		closedir(dir);
	free(str);
}

static char	*advanced_join(char *str, char *path, char *cmd_name)
{
	if (!path)
	{
		if (cmd_name)
			return (ft_strjoin_free(str, cmd_name, 1, 0));
		return (str);
	}
	return (ft_strjoin_free(str, path, 1, 0));
}

static DIR	*open_paths(char *path, int *fd)
{
	DIR	*dir;

	*fd = 0;
	dir = NULL;
	if (path != NULL && ft_strchr(path, '/'))
	{
		*fd = open(path, O_WRONLY);
		dir = opendir(path);
	}
	return (dir);
}

static int	error_print(char *path, char *cmd_name)
{
	char	*str;
	DIR		*dir;
	int		err;
	int		fd;

	fd = 0;
	str = ft_strdup("minishell: ");
	dir = open_paths(path, &fd);
	str = advanced_join(str, path, cmd_name);
	if (path == NULL || ft_strchr(path, '/') == NULL)
		str = ft_strjoin_free(str, ": command not found", 1, 0);
	else if (fd == -1 && dir == NULL)
		str = ft_strjoin_free(str, ": No such file or directory", 1, 0);
	else if (fd == -1 && dir != NULL)
		str = ft_strjoin_free(str, ": Is a directory", 1, 0);
	else if (fd != -1 && dir == NULL)
		str = ft_strjoin_free(str, ": Permission denied", 1, 0);
	if ((!path || !ft_strchr(path, '/')) || (fd == -1 && !dir))
		err = ERR_UNK;
	else
		err = ERR_DIR;
	print_free_close(str, fd, dir, err);
	return (err);
}

void	execute_process(t_hellmini *shell, char *path, char **args)
{
	int	errnoa;

	errnoa = 0;
	signal(SIGINT, control_slash);
	signal(SIGQUIT, control_slash);
	if (execve(path, args, shell->env))
		errnoa = error_print(path, args[0]);
	clear_history();
	free_shell(shell);
	free(path);
	exit(errnoa);
}
