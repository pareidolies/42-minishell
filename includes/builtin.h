#ifndef BUILTIN_H
# define BUILTIN_H
# include "minishell.h"

int		nb_param(char **params);
int		cd_others(/*t_command_table *table, */char **params, t_env *envlist);
int		update_env(char *key, char *newvalue, t_env	*envlist);
t_env	*ft_new_var_split(char *key, char *value);
t_env	*ft_getenv_var(char *key, t_env *envlist);
int		ft_export(char **params, t_env *envlist);
char	*find_name(char *str);
int		valid_identifier(char *name);
void	ft_delenv(t_env *var, t_env *envlist);

#endif