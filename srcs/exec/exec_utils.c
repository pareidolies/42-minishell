/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:31:46 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/09 18:02:51 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

/*Declaring global variable*/
/*As often as needed*/
extern int	g_exit_status;

void	ft_lstaddback(t_env **alst, t_env *new)
{
	t_env	*elt;

	if (*alst == NULL)
		*alst = new;
	else
	{
		elt = *alst;
		while (elt->next != NULL)
			elt = elt->next;
		elt->next = new;
	}
}

void	ft_clean_list(t_env	*envlist)
{
	t_env	*tmp;

	while (envlist != NULL)
	{
		magic_malloc(FREE, 0, envlist->key);
		magic_malloc(FREE, 0, envlist->value);
		tmp = envlist->next;
		magic_malloc(FREE, 0, envlist);
		envlist = tmp;
	}
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
		return (head); //voir variables présentes au démarrage
	i = 0;
	while (envp[i] != NULL)
	{
		var = ft_new_var(envp[i]);
		ft_lstaddback(&head, var);
		i++;
	}
	return (head);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		magic_malloc(FREE, 0, tab[i]);
		i++;
	}
	magic_malloc(FREE, 0, tab);
}
