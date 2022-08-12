/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:58:07 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/12 12:52:14 by lmurtin          ###   ########.fr       */
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
	return (error);
}

int	print_errors_2(int error, char *str)
{
	if (error == COMMAND_ERROR)
	{
		ft_putstr_fd_color(COMMAND_ERR_MSSG, 2, ANSI_COLOR_LIGHT_RED);
		ft_putstr_fd_color(str, 2, ANSI_COLOR_LIGHT_RED);
		ft_putstr_fd("\n", 2);
	}
	if (error == OPEN_ERROR)
	{
		ft_putstr_fd_color(OPEN_ERR_MSSG, 2, ANSI_COLOR_LIGHT_RED);
		ft_putstr_fd_color(str, 2, ANSI_COLOR_LIGHT_RED);
		ft_putstr_fd("\n", 2);
	}
	if (error == PIPE_ERROR)
	{
		ft_putstr_fd_color(PIPE_ERR_MSSG, 2, ANSI_COLOR_LIGHT_RED);
		ft_putstr_fd_color(str, 2, ANSI_COLOR_LIGHT_RED);
		ft_putstr_fd("\n", 2);
	}
	if (error == FORK_ERROR)
	{
		ft_putstr_fd_color(FORK_ERR_MSSG, 2, ANSI_COLOR_LIGHT_RED);
		ft_putstr_fd_color(str, 2, ANSI_COLOR_LIGHT_RED);
		ft_putstr_fd("\n", 2);
	}
	return (error);
}

int	print_errors_3(int error, char *str)
{
	if (error == HEREDOC_WARNING)
	{
		ft_putstr_fd_color(HD_ERR_MSG, 2, ANSI_COLOR_YELLOW);
		ft_putstr_fd_color(str, 2, ANSI_COLOR_YELLOW);
	}
	if (error == 126)
	{
		ft_putstr_fd_color("Is a directory: ", 2, ANSI_COLOR_LIGHT_RED);
		ft_putstr_fd_color(str, 2, ANSI_COLOR_LIGHT_RED);
		ft_putstr_fd("\n", 2);
	}
	if (error == EX_ERROR)
	{
		ft_putstr_fd_color(EX_ERR_MSSG, 2, ANSI_COLOR_LIGHT_RED);
		ft_putstr_fd_color(str, 2, ANSI_COLOR_LIGHT_RED);
		ft_putstr_fd("\n", 2);
		return (126);
	}
	return (error);
}
