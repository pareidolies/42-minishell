/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 15:53:05 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/13 13:38:06 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	set_signals_as_prompt(void)
{
	signal(SIGINT, signal_handler_as_prompt);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSEGV, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
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

int	set_signals_as_parent(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}
