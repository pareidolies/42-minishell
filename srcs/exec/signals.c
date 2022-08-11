/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 15:53:05 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/10 15:25:22 by lmurtin          ###   ########.fr       */
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
	signal(SIGQUIT, signal_handler_as_child);
	return (1);
}

int	set_signals_as_heredoc(void)
{
	signal(SIGINT, signal_handler_as_heredoc);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}

//SIGTERM ?

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
		rl_redisplay();
	}
}

void	signal_handler_as_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		//printf("\n\ncoucou\n\n");
		g_exit_status = 130;
		close(60);
		write(STDOUT_FILENO, "\n", 1);
	}
}

void	signal_handler_as_child(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 130;
		write(STDIN_FILENO, "\n", 1);
		magic_malloc(130, 0, NULL);
	}
	if (signum == SIGQUIT)
	{
		g_exit_status = 131;
		write(STDIN_FILENO, "\n", 1);
		magic_malloc(131, 0, NULL);
	}
}
