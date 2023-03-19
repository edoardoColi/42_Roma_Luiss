/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 04:14:26 by eddy              #+#    #+#             */
/*   Updated: 2023/03/12 22:18:01 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

static int	adhoc_main_echo(int argc, char *argv[], char *env[]);
static int	adhoc_main_cd(int argc, char *argv[], char *env[]);
static int	adhoc_main_pwd(int argc, char *argv[], char *env[]);
static int	adhoc_main_export(int argc, char *argv[], char *env[]);
static int	adhoc_main_unset(int argc, char *argv[], char *env[]);
static int	adhoc_main_env(int argc, char *argv[], char *env[]);
static int	adhoc_main_exit(t_command *commands, char *env[]);

/*
*/
int	do_builtin(const char *path, char *const *argv, char *const *env, t_command **commands)
{
	int	len;
	int	argc;

	argc = 0;
	while (argv[argc])
		argc++;
	len = ft_strlen(path);
	if (ft_strncmp(path, "echo\0", 5) == 0 || ft_strncmp(path, "cd\0", 3) == 0 || ft_strncmp(path, "pwd\0", 4) == 0 || ft_strncmp(path, "export\0", 7) == 0 || ft_strncmp(path, "unset\0", 6) == 0 || ft_strncmp(path, "env\0", 4) == 0 || ft_strncmp(path, "exit\0", 5) == 0)
	{
		if (ft_strncmp(path, "echo\0", 5) == 0)
			return (adhoc_main_echo(argc, (char**) argv, (char**) env));
		if (ft_strncmp(path, "cd\0", 3) == 0)
			return (adhoc_main_cd(argc, (char**) argv, (char**) env));
		if (ft_strncmp(path, "pwd\0", 4) == 0)
			return (adhoc_main_pwd(argc, (char**) argv, (char**) env));
		if (ft_strncmp(path, "export\0", 7) == 0)
			return (adhoc_main_export(argc, (char**) argv, (char**) env));
		if (ft_strncmp(path, "unset\0", 6) == 0)
			return (adhoc_main_unset(argc, (char**) argv, (char**) env));
		if (ft_strncmp(path, "env\0", 4) == 0)
			return (adhoc_main_env(argc, (char**) argv, (char**) env));
		if (ft_strncmp(path, "exit\0", 5) == 0)
			return (adhoc_main_exit(*commands, (char**) env));
		return (0);
	}
	return (2);
}

/*
*/
int	adhoc_main_echo(int argc, char *argv[], char *env[])
{
	int i;
	int no_newline = 0;

	if (argc > 1 && ft_strncmp(argv[1], "-n\0", 3) == 0)// Check for the -n option
	{
		no_newline = 1;
		argc--;
		argv++;
	}	
	for (i = 1; i < argc; i++)// Print the remaining arguments
	{
		printf("%s", argv[i]);
		if (i < argc - 1)
			printf(" ");
	}
	if (!no_newline)// Print a newline unless the -n option was used
		printf("\n");
	return 0;
}

/*
*/
int	adhoc_main_cd(int argc, char *argv[], char *env[])
{
	char	*home;
	char	cwd[MAX_NAME];
	char	target_path[MAX_NAME];

	if (argc > 2)// check for correct number of arguments
	{
		printf("bash: %s: too many arguments\n", argv[0]);
		return 1;
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)// get current working directory
	{
		perror("Fail getcwd\n");
		return 1;
	}
	if (argc == 1)
	{
		home = adhoc_getenv("HOME", env);
		if (chdir(home) == -1)
		{
			perror("Fail chdir\n");
			return 1;
		}
		adhoc_setenv("PWD", home, env);// change working directory to target path
		adhoc_setenv("OLDPWD", cwd, env);// change old working directory to target path
	} else
	{
		ft_memset(target_path, '\0', MAX_NAME);
		if (argv[1][0] == '/')// absolute path
			ft_strlcat(target_path, argv[1], MAX_NAME);
		else// relative path
		{
			ft_strlcat(target_path, cwd, MAX_NAME);
			ft_strlcat(target_path, "/\0", MAX_NAME);
			ft_strlcat(target_path, argv[1], MAX_NAME);
		}
		if (access(target_path, F_OK) != 0)
		{
			if (errno == ENOENT)
				printf("bash: cd: %s: no such file or directory\n", argv[1]);
			else
				perror("Fail access\n");
			return 1;
		}
		if (chdir(target_path) == -1)
		{
			perror("Fail chdir\n");
			return 1;
		}
		if (getcwd(target_path, sizeof(target_path)) == NULL)// get new working directory
			{
				perror("Fail getcwd\n");
				return 1;
		}
		adhoc_setenv("PWD", target_path, env);// change working directory to target path
		adhoc_setenv("OLDPWD", cwd, env);// change old working directory to target path
	}
	return 0;
}

/*
*/
int	adhoc_main_pwd(int argc, char *argv[], char *env[])
{
	char	cwd[MAX_NAME];

	if (getcwd(cwd, sizeof(cwd)) == NULL)// get new working directory
		{
			perror("Fail getcwd\n");
			return 1;
	}
	printf("%s\n", cwd);
	return 0;
}

/*
*/
int	adhoc_main_export(int argc, char *argv[], char *env[])
{
	int		i;
	int		j;
	int		flag;
	int		ret;
	char	name[MAX_NAME];
	char	val[MAX_NAME];

	ret = 0;
	if (argc < 2) {
		printf("bash: export: usage: export [name=value ...] \n");
		return (1);
	}
	i = 0;
	while (argv[++i])
	{
		ft_memset(name, '\0', MAX_NAME);
		ft_memset(val, '\0', MAX_NAME);
		flag = -1;
		j = -1;
		while (argv[i][++j] != '\0')
		{
			if (argv[i][j] == '=' && flag == -1)//ricordo dov'e' il primo uguale
			{
				flag = j;
				j++;
			}
			if(flag == -1)
				name[j] = argv[i][j];
			else
				val[j - flag - 1] = argv[i][j];
		}
		if (flag == 0)
		{
			printf("bash: export: `%s': not a valid identifier\n",argv[i]);
			ret = 1;
		}
		if (flag != -1 && flag != 0)
			adhoc_setenv(name, val, env);
	}
	return (ret);
}

/*
*/
int	adhoc_main_unset(int argc, char *argv[], char *env[])
{
	int		i;
	int		j;
	int		len;
	int		flag;
	char	*tmp;

	i = 0;
	while (argv[++i])
	{
		flag = 0;
		len = ft_strlen(argv[i]);
		j = -1;
		while (env[++j] != NULL)
		{
			if (flag == 0 && ft_strncmp(env[j], argv[i], len) == 0 && env[j][len] == '=')
			{
				flag = 1;
				tmp = env[j];
			}
			else if (flag == 1)
				env[j - 1] = env[j];
		}
		if (flag == 1)
		{
			free(tmp);
			env[j - 1] = NULL;
		}
	}
	return 0;
}

/*
*/
int	adhoc_main_env(int argc, char *argv[], char *env[])
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
	 printf("%s\n",env[i]);
	return 0;
}

/*
*/
int	adhoc_main_exit(t_command *commands, char *env[])
{
	int	i;
	int	j;

	i = -1;
	while (++i < commands[0].n_cmds)	//free loop for memory in the commands[i] arrays
	{
		j = -1;
		while (++j < MAX_ENTRY)	//free loop for memory in the commands[i].arrays strings
		{
			free(commands[i].args[j]);
			free(commands[i].rdr_in[j]);
			free(commands[i].rdr_out[j]);
			free(commands[i].heredoc[j]);
			free(commands[i].append[j]);
		}
		free(commands[i].args);
		free(commands[i].rdr_in);
		free(commands[i].rdr_out);
		free(commands[i].heredoc);
		free(commands[i].append);
	}
	free(commands);
	i = -1;
	while (env[++i])
		free(env[i]);
	free(env);
	exit(1);
}