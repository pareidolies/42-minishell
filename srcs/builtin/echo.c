#include <stdio.h>

/*Supposant que la commande est stockée avec ses arguments dans un tableau de char */
/*params[0] = nom commande*/
ft_echo(char **params)
{
	int		option;
	int		i;
	char	*str;

	option = 0;
	i = 1;
	/* /!\ Faire verif des arguments*/
	if (ft_strncmp(params[1], "-n", 3) == 0)
	{
		option = 1;
		i++;
	}
	
}