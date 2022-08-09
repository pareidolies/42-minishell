/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:58:07 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/09 16:00:22 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd_color(char *str, int fd, char *color)
{
	ft_putstr_fd(color, fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd(ANSI_COLOR_RESET, fd);
}

int	print_errors(int error)
{
	if (error == QUOTES_ERROR)
		ft_putstr_fd_color(QUOTES_ERR_MSSG, 2, ANSI_COLOR_LIGHT_RED);
	if (error == TOKENS_ERROR)
		ft_putstr_fd_color(TOKENS_ERR_MSSG, 2, ANSI_COLOR_LIGHT_RED);
	if (error == MALLOC_ERROR)
		ft_putstr_fd_color(MALLOC_ERR_MSSG, 2, ANSI_COLOR_LIGHT_RED);
	if (error == COMMAND_ERROR)
		ft_putstr_fd_color(COMMAND_ERR_MSSG, 2, ANSI_COLOR_LIGHT_RED);
	return (error);
}
