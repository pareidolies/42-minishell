#ifndef MINISHELL_H

# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

/******************************************************************************
 *                             ENUMERATIONS                                   *
 *****************************************************************************/

//Tokens types

typedef enum e_type
{
	T_LITERAL,
    T_LESS,
    T_INPUT,
    T_GREATER,
    T_OUTPUT,
    T_D_LESS,
    T_DELIMITER,
    T_D_GREATER,
    T_APPEND,
	T_PIPE,
    T_AND,
    T_OR,
}	t_type;

/******************************************************************************
 *                                 MACROS                                     *
 *****************************************************************************/

//Characters

# define S_QUOTE '\''
# define D_QUOTE '"'
# define SPACE ' '
# define LESS '<'
# define GREATER '>'
# define PIPE '|'

//Strings

# define STR_LESS "<"
# define STR_D_LESS "<<"
# define STR_GREATER ">"
# define STR_D_GREATER ">>"
# define STR_PIPE "|"

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
    char    *trimmed_token;
    t_type     type;
    int         to_expand;
    struct s_token *next;
    struct s_token *prev;
}   t_token;

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
void main_parser(char *str);

//token_handler.c
void    print_tokens(t_token *token);
void add_token(t_token *list, char *str, int flag);
t_token *create_token(char *str, int flag);

//tokenization.c
int	analyze_quotes(char *str);
int	get_token_size(char *str);
t_token	*tokenization(char *str);
void	analyze_tokens_type(t_token *list);
void	analyze_literals_type(t_token *list);
void main_parser(char *str);

//expander.c
int there_is_a_dollar(char *str);
void    analyze_tokens_to_expand(t_token *list);

//trim_tokens.c
void    trim_tokens(t_token *list);

#endif
