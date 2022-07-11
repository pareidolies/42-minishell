#ifndef MINISHELL_H

# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>

/******************************************************************************
 *                               STRUCTURES                                   *
 *****************************************************************************/

typedef struct s_command_table 
{
    t_list *commands;
    char	**env;
	pid_t	pid;
}   t_command_table;

typedef struct s_command
{
    char	*cmd;
	char	*path; //NULL if its a builtin
    char    **options;
    char    **parameters;
	int		infile; //default stdin
	int		outfile; //default stdout
    struct s_command *next;
    struct s_command *prev;
}   t_command;

typedef struct s_token
{
    char    *token;
    int     flag;
    struct s_token *next;
    struct s_token *prev;
}   t_token;

/******************************************************************************
 *                             ENUMERATIONS                                   *
 *****************************************************************************/

typedef enum e_type
{
	LITERAL,
    LESS,
    GREATER,
    LESS_LESS,
    GREATER_GREATER,
	PIPE,
	WHITESPACE,
	SIMPLE_QUOTE,
	DOUBLE_QUOTE,
    AND,
    OR,
}	t_type;

/******************************************************************************
 *                                 MACROS                                     *
 *****************************************************************************/


/******************************************************************************
 *                            GLOBAL VARIABLE                                 *
 *****************************************************************************/

int g_exit_status;

/******************************************************************************
 *                               FUNCTIONS                                    *
 *****************************************************************************/

//testmain.c
int	exe_command(char **commandfull);
char    *environment_path(char *command, char *path_var);
char	*absolute_relative_path(char *command);





#endif
