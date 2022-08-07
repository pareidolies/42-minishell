/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 15:53:05 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/07 15:53:07 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_exit_status;

int	set_signals_as_prompt(void)
{
	signal(SIGINT, signal_handler_as_prompt);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}

int	set_signals_as_here_doc(void)
{
	signal(SIGINT, signal_handler_as_prompt);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}

void	signal_handler_as_prompt(int signum)
{
	if (signum == SIGINT)
    {
		g_exit_status = 1;
		ft_putstr_fd("\n", 1);
		set_line();
    }
}

void	signal_handler_as_here_doc(int signum)
{
	if (signum == SIGINT)
    {
		g_exit_status = 130;
		magic_malloc(QUIT, 0, NULL);
    }
}

//ajouter signal handler as parent and children ?