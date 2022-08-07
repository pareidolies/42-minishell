/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   say_hello.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 15:53:13 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/07 15:53:14 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    say_hello(void)
{
	ft_putstr_fd("\e[1;1H\e[2J", 1);
	ft_putstr_fd_color("\n\n", 1, ANSI_COLOR_LIGHT_YELLOW);
	ft_putstr_fd_color(L1, 1, ANSI_COLOR_LIGHT_YELLOW);
	ft_putstr_fd_color(L2, 1, ANSI_COLOR_LIGHT_YELLOW);
	ft_putstr_fd_color(L3, 1, ANSI_COLOR_LIGHT_YELLOW);
	ft_putstr_fd_color(L4, 1, ANSI_COLOR_LIGHT_YELLOW);
	ft_putstr_fd_color(L5, 1, ANSI_COLOR_LIGHT_YELLOW);
	ft_putstr_fd_color(L6, 1, ANSI_COLOR_LIGHT_YELLOW);
	ft_putstr_fd_color(L7, 1, ANSI_COLOR_BOLD_CYAN);
	ft_putstr_fd_color(L8, 1, ANSI_COLOR_BOLD_CYAN);
	ft_putstr_fd_color("\n\n", 1, ANSI_COLOR_CYAN);
}
