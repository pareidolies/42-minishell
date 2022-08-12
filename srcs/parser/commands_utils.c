/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:24:13 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/12 12:24:16 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '\0')
		return (2);
	if (!ft_strncmp(str, "echo", ft_strlen(str)))
		return (1);
	if (!ft_strncmp(str, "cd", ft_strlen(str)))
		return (1);
	if (!ft_strncmp(str, "pwd", ft_strlen(str)))
		return (1);
	if (!ft_strncmp(str, "export", ft_strlen(str)))
		return (1);
	if (!ft_strncmp(str, "unset", ft_strlen(str)))
		return (1);
	if (!ft_strncmp(str, "env", ft_strlen(str)))
		return (1);
	if (!ft_strncmp(str, "exit", ft_strlen(str)))
		return (1);
	return (0);
}
