/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 15:53:05 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/09 11:22:48 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	set_signals_as_prompt(void)
{
	signal(SIGINT, signal_handler_as_prompt);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}

int	set_signals_as_child(void)
{
	signal(SIGINT, signal_handler_as_child);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}

int	set_signals_as_parent(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}

void	signal_handler_as_prompt(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 130;
		//ft_putstr_fd("\n", 1);
		write(STDIN_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	signal_handler_as_child(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 1;
		magic_malloc(1, 0, NULL);
	}
}

//ajouter signal handler as parent and children ?
