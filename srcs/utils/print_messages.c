/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:58:07 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/04 12:58:23 by smostefa         ###   ########.fr       */
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
		printf(QUOTES_ERR_MSSG);
	if (error == TOKENS_ERROR)
		printf(TOKENS_ERR_MSSG);
	return (error);
}
