/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:31:23 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/13 12:21:32 by lmurtin          ###   ########.fr       */
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

t_env	*ft_new_var(char *keyvalue)
{
	t_env	*var;
	int		i;
	int		j;

	i = 0;
	var = magic_malloc(MALLOC, sizeof(t_env), NULL);
	if (var == NULL)
		return (perror("ft_new_var "), NULL);
	while (keyvalue[i] != '\0')
	{
		if (keyvalue[i] == '=')
			j = i;
		i++;
	}
	var->key = ft_substr(keyvalue, 0, j);
	magic_malloc(ADD, 0, var->key);
	if (var->key == NULL)
		return (perror("ft_new_var "), NULL);
	var->value = ft_substr(keyvalue, j + 1, i - (j + 1));
	magic_malloc(ADD, 0, var->value);
	if (var->value == NULL)
		return (perror("ft_new_var "), NULL);
	var->next = NULL;
	return (var);
}

/*head contient $? et sa valeur g_exit_status*/
t_env	*ft_list_env(char **envp)
{
	t_env	*var;
	t_env	*head;
	int		i;

	var = NULL;
	head = magic_malloc(MALLOC, sizeof(t_env), NULL);
	head->key = ft_strdup("?");
	magic_malloc(ADD, 0, head->key);
	head->value = ft_strdup("0");
	magic_malloc(ADD, 0, head->value);
	head->next = NULL;
	if (envp == NULL || envp[0] == NULL)
	{
		init_empty_env(&head);
		return (head);
	}
	i = 0;
	while (envp[i] != NULL)
	{
		var = ft_new_var(envp[i]);
		ft_lstaddback(&head, var);
		i++;
	}
	return (head);
}

void	init_empty_env(t_env **head)
{
	t_env	*var;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	var = ft_new_var_split("PWD", pwd);
	ft_lstaddback(head, var);
	var = ft_new_var_split("SHLVL", "1");
	ft_lstaddback(head, var);
	var = ft_new_var_split("_", "/usr/bin/env");
	ft_lstaddback(head, var);
	free(pwd);
}
