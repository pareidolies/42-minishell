#include "../../includes/minishell.h"
#include "builtin.h"

int	ft_export(char **params, t_env *envlist)
{
	int		i;
	char	*eq_position;
	char	*key;

	if (nb_param(params) < 1)
	{
		write(2, "export : Too few arguments\n", 27);
		return (1);
	}
	i = 1;
	while (params[i] != NULL)
	{
		eq_position = ft_strchr(params[i], '=');
		if (eq_position == NULL) //export VARIABLE
		{
			if (valid_identifier(params[i]) == 0)
				update_env(params[i], NULL, envlist);
			else
			{
				write(2, "export : Not a valid identifier\n", 31); /*GESTION ERREUR*/
				//exit status = 1
			}
		}
		else 
		{
			key = find_name(params[i]);
			if (valid_identifier(key) == 0 && eq_position[1] == '\0') //export VARIABLE=
				update_env(key, "", envlist);
			else if (valid_identifier(key) == 0) //export VARIABLE=value
				update_env(key, eq_position + 1, envlist);
			else
			{
				write(2, "export : Not a valid identifier\n", 31); /*GESTION ERREUR*/
				//exit status = 1
			}
			free(key);
		}
		i++;
	}
	return (0);
}

char	*find_name(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while(str[i] != '=')
		i++;
	name = ft_substr(str, 0, i);
	if (name == NULL)
		return (NULL); /*GESTION ERREUR MALLOC*/
	return (name);
}

/*Variable name must be only composed of letters, underscores and digits*/
/*Digits NEVER in starting position, No special character included*/
int	valid_identifier(char *name)
{
	int	i;

	i = 0;
	if (name[0] >= '0' && name[0] <= '9')
		return (1);
	while (name[i] != '\0')
	{
		if (ft_isalnum(name[i]) == 1 && name[i] != '_')
			return (1);
		i++;
	}
	return (0);
}