/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 12:55:24 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/13 13:40:14 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler_as_prompt(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 130;
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
