#include "minishell.h"
#include "builtin.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

/*Declaring global variable*/
/*As often as needed*/
extern int g_exit_status;

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

/*head contient $? et sa valeur g_exit_status*/
t_env	*ft_list_env(char **envp)
{
	t_env	*var;
	t_env	*head;
	int		i;

	var = NULL;
	head = malloc(sizeof(t_env));
	if (head == NULL)
		return (perror("ft_list_end "), NULL); /*GESTION ERREUR MALLOC*/
	head->key = ft_strdup("?");
	head->value = ft_strdup("0");
	head->next = NULL;
	if (head->key == NULL || head->value == NULL)
		return (perror("ft_list_end "), NULL); /*GESTION ERREUR MALLOC*/
	if (envp == NULL || envp[0] == NULL)
		return (head); //voir variables présentes au démarrage
	i = 0;
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

//g_exit_status est un int, et la fonction retourne un char*
//SOLVED : $? est maintenant gérée comme une variable d'env normale 

char *ft_getenv(char *key, t_env *envlist)
{
	while (envlist != NULL)
	{
		if (ft_strncmp(envlist->key, key, ft_strlen(key) + 1) == 0)
			return (envlist->value);
		envlist = envlist->next;
	}
	return ("");
}

int	ft_update_status(int code, t_env *envlist)
{
	char	*newvalue;

	if (code == g_exit_status)
		return (0);
	newvalue = ft_itoa(code);
	if (newvalue == NULL)
	{
		perror("ft_update_status "); /*GESTION ERREUR MALLOC*/
		return (1);
	}
	update_env("?", newvalue, envlist);
	g_exit_status = code;
	return (0);
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