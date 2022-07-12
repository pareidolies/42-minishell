#include "builtin.h"

int	nb_param(char **params)
{
	int	i;

	i = 0;
	while (params[i] != NULL)
	{
		i++;
	}
	return (i);
}