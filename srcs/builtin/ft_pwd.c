/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:30:48 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/07 21:40:32 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

/* Return values OK */

int	ft_pwd(char **params)
{
	char		*path;
	int			error;

	if (nb_param(params) > 1 && params[1][0] == '-')
	{
		write(2, "pwd : Invalid option\n", 21); /*GESTION ERREUR*/
		return (2);
	}
	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		perror("pwd ");
		error = errno;
		return (error); /*GESTION ERREUR*/
	}
	printf("%s\n", path);
	free(path);
	return (0);
}
