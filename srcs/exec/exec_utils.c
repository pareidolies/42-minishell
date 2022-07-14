#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

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

t_env	*ft_new_var(char *keyvalue)
{
	t_env	*var;
	int		i;
	int		j;
	
	i = 0;
	var = malloc(sizeof(t_env));
	if (var == NULL)
		return (perror("ft_new_var "), NULL); /*GESTION D'ERREUR*/
	while(keyvalue[i] != '\0')
	{
		if (keyvalue[i] == '=')
			j = i;
		i++; 
	}
	var->key = ft_substr(keyvalue, 0, j);
	if (var->key == NULL)
		return (perror("ft_new_var "), NULL);
	var->value = ft_substr(keyvalue, j + 1, i - (j + 1));
	if (var->value == NULL)
		return (perror("ft_new_var "), NULL);
	var->next = NULL;
	return (var);
}

t_env	*ft_list_env(char **envp)
{
	t_env	*var;
	t_env	*head;
	int		i;

	i = 1;
	var = NULL;
	if (envp == NULL || envp[0] == NULL)
		return (NULL);
	head = ft_new_var(envp[0]);
	if (head == NULL)
		return(NULL); //faire fonction clean_exit !!
	while (envp[i] != NULL)
	{
		var = ft_new_var(envp[i]); /*create a new node and fill it*/
		ft_lstaddback(&head, var);
		i++;
	}
	return (head);
}

void	ft_clean_list(t_env	*envlist)
{
	t_env	*tmp;

	while (envlist != NULL)
	{
		free(envlist->key);
		free(envlist->value);
		tmp = envlist->next;
		free(envlist);
		envlist = tmp;
	}
}

char *ft_getenv(char *key, t_env *envlist)
{
	while (envlist != NULL)
	{
		if (ft_strncmp(envlist->key, key, ft_strlen(key) + 1) == 0)
			return (envlist->value);
		envlist = envlist->next;
	}
	printf("Variable [%s] not in the environment.\n", key);
	return (NULL);
}

/*usage : ./a.out KEY */
// int main(int argc, char **argv, char **envp)
// {
// 	char	*result;
// 	t_env	*envlist;

// 	if (argc != 2 || argv[2] != NULL)
// 		return(1);
// 	envlist = ft_list_env(envp);
// 	result = ft_getenv(argv[1], envlist);
// 	printf("key = %s\nvalue = [%s]\n", argv[1], result);
// 	ft_clean_list(envlist);
// 	return (0);
// }