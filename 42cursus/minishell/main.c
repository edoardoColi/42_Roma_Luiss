/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:17:40 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:29:44 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "glob.h"
#include "executor.h"

static char	*prompt_part_2(t_hellmini *shell)
{
	char	*prompt;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_sigs_handler);
	prompt = our_prompt(shell, getcwd(NULL, 0));
	return (prompt);
}

static int	prompt_loop(t_hellmini *shell)
{
	char	*prompt;

	while (TRUE)
	{
		prompt = prompt_part_2(shell);
		shell->input = readline(prompt);
		free(prompt);
		if (!shell->input)
		{
			write(1, "\rexit\n", 7);
			break ;
		}
		if (ft_strncmp(shell->input, "", 1))
			add_history(shell->input);
		if (lexer_init(shell) == 0)
		{
			if (parser(shell) == SUCCESS)
				ft_executor(shell->current_cmd);
		}
		free_commands(shell);
		free(shell->input);
	}
	clear_history();
	free_shell(shell);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_hellmini	*shell;

	(void)argc;
	(void)argv;
	shell = (t_hellmini *) malloc(sizeof(t_hellmini));
	if (!shell)
		return (EXIT_FAILURE);
	init_shell(shell, env);
	prompt_loop(shell);
	return (0);
}
