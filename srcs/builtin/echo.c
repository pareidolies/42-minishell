#include <stdio.h>
#include "builtin.h"
#include "../../libft/libft.h"
#include "../../includes/minishell.h"

int	is_valid_option(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-')
	{
		while (str[i] != '\0')
		{
			if (str[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	else
		return (1);
}

/*Supposant que la commande est stockée avec ses arguments dans un tableau de char */
/*params[0] = nom commande*/
int	ft_echo(char **params)
{
	int		option;
	int		i;

	option = 0;
	i = 1;//=0
	if (nb_param(params) == 1)//==0
		write(1, "\n", 1);
	else if (nb_param(params) == 2/*==1*/ && is_valid_option(params[1]) == 0)
		return (0);
	else
	{
		while (is_valid_option(params[i]) == 0)
		{
			option = 1;
			i++;
			if (params[i] == NULL)
				return (0);
		}
		while (params[i + 1] != NULL)
		{
			printf("%s", params[i]);
			printf(" ");
			i++;
		}
		if (params[i] != NULL)
			printf("%s", params[i]);
		if (option != 1)
			printf("\n");
	}
	return (0);
}

int main(int argc, char **argv)
{
	char	**params;

	if (argc < 1)
		return (1);
	params = argv;
	ft_echo(params);
	return (0);
}