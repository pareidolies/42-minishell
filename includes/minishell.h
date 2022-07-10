#ifndef MINISHELL_H

# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>

//testmain.c
int	exe_command(char **commandfull);
environment_path(char *command, char *path_var);
char	*absolute_relative_path(char *command);





#endif
