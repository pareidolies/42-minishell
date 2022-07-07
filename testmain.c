#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

/*test affichage du prompt et recup de la ligne*/
int main(void)
{
	char	*result;
	int		flag;
	
	result = getenv("PWD");
	printf("PWD = [%s]\n", result);
	flag = pathconf("testmain.c", _PC_PATH_MAX);
	printf("flag = %d\n", flag);
	printf("OLDPWD = [%s]\n", getenv("OLDPWD"));
	// while (flag != 1) 
	// {
	// result = readline("minishell>> ");
	// printf("User said : [%s]\n", result);
	// add_history(result);
	// if (strcmp(result, "aurevoir") == 0)
	// 	flag = 1;
	// free(result);
	// }
	// rl_clear_history();
	return (0);
}

// /*Une fois que le parser nous a permis de recup un tableau de string*/
// /*constitué de la commande et ses argument :*/
// int	exe_command(char **command)
// {
// 	char	*path_var;
// 	char	*path;

// 	/*savoir si on a déjà un chemin ou si on doit aller le chercher dans l'env*/
// 	if (command[0] contient un '/')
// 		traiter_absolute_relative_path(command[0]);
// 	else
// 	{
// 		path_var = getenv("PATH");
// 		printf("key = PATH, value = [%s]\n", path);
// 	}
// }
