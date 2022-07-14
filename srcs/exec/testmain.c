#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

/*test affichage du prompt et recup de la ligne*/
int main(void)
{
	char	*result;
	int		flag;
	
	// result = getenv("PWD");
	// printf("PWD = [%s]\n", result);
	// flag = pathconf("testmain.c", _PC_PATH_MAX);
	// printf("flag = %d\n", flag);
	// printf("OLDPWD = [%s]\n", getenv("OLDPWD"));
	flag = 0;
	while (flag != 1) 
	{
		result = readline("minishell>> ");
		printf("User said : [%s]\n", result);
		add_history(result);
		main_parser(result);
		if (strcmp(result, "aurevoir") == 0)
			flag = 1;
		free(result);
	}
	clear_history();
	return (0);
}
