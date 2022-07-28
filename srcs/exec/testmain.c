#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

/*Defining and initializing global variable*/
/*only once in the program*/
int g_exit_status = 0; 

/*test affichage du prompt et recup de la ligne*/
/*pour l'instant, le prog quitte si on tape "aurevoir" */
/*PAS ENCORE DE NETTOYAGE COMPLET DONC LEAKS*/
int main(int argc, char **argv, char **envp)
{
	char	*result;
	t_env	*envlist;
	int		flag;
	t_command *commands;
	//char	**params;
	
	flag = 0;
	if (argc != 1 || argv[1] != NULL)
		return(1);
	
	/*Une seule fois, on crée la liste d'env en dupliquant envp*/
	/*liste peut être modifiée une ou + fois par ligne de cmd*/
	envlist = ft_list_env(envp);

	while (flag != 1) 
	{
		result = readline("minishell>> ");
		printf("User said : [%s]\n", result);
		if (ft_strncmp(result, "exit", 5) == 0)
			flag = 1;
		add_history(result);
		commands = main_parser(result, envlist);
		//ft_exec(commands, envlist);
		exec_no_pipeline(commands, envlist);
		free_commands(commands);
		free(result);
	}
	clear_history();
	ft_clean_list(envlist);
	return (0);
}
