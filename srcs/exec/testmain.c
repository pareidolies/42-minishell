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

void	set_line(void)
{
	if (g_exit_status == 0)
		ft_putstr_fd_color("➜ ", 1, ANSI_COLOR_GREEN);
	else
		ft_putstr_fd_color("➜ ", 1, ANSI_COLOR_ORANGE);
	ft_putstr_fd_color("minishell» ", 1, ANSI_COLOR_BOLD_CYAN);
}

int main(int argc, char **argv, char **envp)
{
	char	*result;
	t_env	*envlist;
	int		flag;
	t_command *commands;
	
	flag = 0;
	if (argc != 1 || argv[1] != NULL)
		return(1);
	
	/*Une seule fois, on crée la liste d'env en dupliquant envp*/
	/*liste peut être modifiée une ou + fois par ligne de cmd*/
	envlist = ft_list_env(envp);
	say_hello();
	while (flag != 1) 
	{
		set_signals_as_prompt();
		set_line();
		result = readline("");
		if (!result)
		{
			ft_putstr_fd_color("\b exit", 2, ANSI_COLOR_LIGHT_YELLOW);
			clear_history();
			magic_malloc(EXIT_SUCCESS, 0, NULL);
		}
		else
		{
			printf("User said : [%s]\n", result);
			if (ft_strncmp(result, "exit", 5) == 0) //dans ce cas il reste 5 file descriptors ouverts
				flag = 1;
			add_history(result);
			commands = parse_input(result, envlist);
			if (!commands)
				free(result);
			else
			{
				ft_exec(commands, envlist);
				free(result);
				free_commands(commands);
			}
		}
	}
	clear_history();
	ft_clean_list(envlist);
	magic_malloc(QUIT, 0, NULL);
	return (0);
}