#ifndef MINISHELL_H

# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

/******************************************************************************
 *                               STRUCTURES                                   *
 *****************************************************************************/

typedef struct s_command_table 
{
    struct s_command *commands;
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
    D_LESS,
    D_GREATER,
	PIPE,
	WHITESPACE,
	S_QUOTE,
	D_QUOTE,
    AND,
    OR,
}	t_type;

/******************************************************************************
 *                                 MACROS                                     *
 *****************************************************************************/

# define S_QUOTE '\''
# define D_QUOTE '"'
# define SPACE ' '
# define LESS '<'
# define GREATER '>'
# define PIPE '|'

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

//main_parser.c



//token_handler.c
void    print_tokens(t_token *token);
void add_token(t_token *list, char *str, int flag);
t_token *create_token(char *str, int flag);

//tokenization.c
int	analyze_quotes(char *str);
int	get_token_size(char *str);
t_token	*tokenization(char *str);


#endif
