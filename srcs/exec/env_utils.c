/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:31:23 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/09 16:33:40 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*ft_getenv(char *key, t_env *envlist)
{
	while (envlist != NULL)
	{
		if (ft_strncmp(envlist->key, key, ft_strlen(key) + 1) == 0)
			return (envlist->value);
		envlist = envlist->next;
	}
	return ("");
}

t_env	*ft_getenv_var(char *key, t_env *envlist)
{
	while (envlist != NULL)
	{
		if (ft_strncmp(envlist->key, key, ft_strlen(key) + 1) == 0)
			return (envlist);
		envlist = envlist->next;
	}
	return (NULL);
}
