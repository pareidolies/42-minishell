/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:33:41 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/07 18:33:53 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe_or_redir_or_quote(char c)
{
	if ((c == SPACE) || (c == PIPE)
		|| (c == GREATER) || (c == LESS)
		|| (c == S_QUOTE) || (c == D_QUOTE))
		return (1);
	return (0);
}

int	is_d_redir(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == LESS && str[i + 1] == LESS)
		|| (str[i] == GREATER
			&& str[i + 1] == GREATER))
		return (1);
	return (0);
}

int	is_s_redir(char c)
{
	if (c == LESS || c == GREATER)
		return (1);
	return (0);
}
