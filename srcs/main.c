/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:02:12 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/12 22:21:08 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Defining and initializing global variable*/
/*only once in the program*/
int	g_exit_status = 0;

char	*get_prompt(void)
{
	char	*prompt;

	if (g_exit_status == 0)
		prompt = "\e[0;32m➜ \x1b[0m\e[1;36mminishell>> \x1b[0m";
	else
		prompt = "\e[1;31m➜ \x1b[0m\e[1;36mminishell>> \x1b[0m";
	return (prompt);
}

void	exit_error_readline(void)
{
	ft_putstr_fd_color("\b exit\n", 2, ANSI_COLOR_LIGHT_YELLOW);
	clear_history();
	magic_malloc(EXIT_FAILURE, 0, NULL);
}

void	start_minishell(char *result, t_env *envlist)
{
	t_command	*commands;

	add_history(result);
	commands = parse_input(result, envlist);
	if (!commands)
		free(result);
	else
	{
		set_signals_as_parent();
		g_exit_status = 0;
		ft_exec(commands, envlist, result);
	}
}

void	end_minishell(t_env *envlist)
{
	clear_history();
	ft_clean_list(envlist);
	magic_malloc(QUIT, 0, NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char		*result;
	t_env		*envlist;
	char		*prompt;

	if (argc != 1 || argv[1] != NULL)
		return (1);
	envlist = ft_list_env(envp);
	say_hello();
	while (1)
	{
		set_signals_as_prompt();
		prompt = get_prompt();
		result = readline(prompt);
		if (!result)
			exit_error_readline();
		else
			start_minishell(result, envlist);
		ft_update_status(envlist);
	}
	end_minishell(envlist);
	return (0);
}
