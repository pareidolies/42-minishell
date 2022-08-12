/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:30:48 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/12 22:45:55 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

/* Return values OK */

int	ft_pwd(char **params, t_env *envlist)
{
	char		*path;

	if (nb_param(params) > 1 && params[1][0] == '-')
	{
		write(2, "pwd : Invalid option\n", 21);
		return (2);
	}
	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		path = ft_strdup(ft_getenv("PWD", envlist));
		if (path == NULL)
			return (perror("pwd: "), 1);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}
