/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 15:53:05 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/11 13:37:07 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	set_signals_as_prompt(void)
{
	// ft_putstr_fd("coucou prompt\n", 2);
	signal(SIGINT, signal_handler_as_prompt);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSEGV, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	return (1);
}

int	set_signals_as_child(void)
{
	// ft_putstr_fd("coucou child\n", 2);
	signal(SIGINT, signal_handler_as_child);
	signal(SIGQUIT, signal_handler_as_child);
	return (1);
}

int	set_signals_as_heredoc(void)
{
	// ft_putstr_fd("coucou heredoc\n", 2);
	signal(SIGINT, signal_handler_as_heredoc);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}

//SIGTERM ?

int	set_signals_as_parent(void)
{
	// ft_putstr_fd("coucou parent\n", 2);
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
		write(STDOUT_FILENO, "\n", 1);
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
		// ft_putstr_fd("HEREDOC\n", 2);
		g_exit_status = 130;
		close(60);
		write(STDOUT_FILENO, "\n", 1);
	}
}

void	signal_handler_as_child(int signum)
{
	// ft_putstr_fd("FONCTION\n", 2);
	if (signum == SIGINT)
	{
		g_exit_status = 130;
		write(STDOUT_FILENO, "\n", 1);
		magic_malloc(130, 0, NULL);
	}
	else if (signum == SIGQUIT)
	{
		write(2, "Quit", 4);
		g_exit_status = 102;
		write(STDOUT_FILENO, "\n", 1);
		magic_malloc(102, 0, NULL);
	}
}
