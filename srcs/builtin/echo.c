#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < (n - 1))
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*Supposant que la commande est stockée avec ses arguments dans un tableau de char */
/*params[0] = nom commande*/
int	ft_echo(char **params)
{
	int		option;
	int		i;
	//char	*str;

	option = 0;
	i = 1;//=0
	if (nb_param(params) == 1)//==0
		write(1, "\n", 1);
	else if (nb_param(params) == 2/*==1*/ && ft_strncmp(params[1]/*[0]*/, "-n", 3) == 0)
		return (0);
	else
	{
		if (ft_strncmp(params[1], "-n", 3) == 0)
		{
			option = 1;
			i++;
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