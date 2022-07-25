#ifndef MINISHELL_H

# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

/******************************************************************************
*                              ENUMERATIONS                                   *
******************************************************************************/

//Tokens types

typedef enum e_type
{
	T_LITERAL,
	T_CMD,
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

//Files

/*typedef enum e_file
{
	INFILE,
	OUTFILE,
	ERROR,
}   t_file;*/

//Redirection modes

typedef enum e_mode
{
	TRUNC, //0 '>'
	APPEND, //1 '>>'
	INFILE, //2 '<'
	DELIMITER, //3 '<<'
}   t_mode;

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
# define DOLLAR '$'

//Strings

# define STR_LESS "<"
# define STR_D_LESS "<<"
# define STR_GREATER ">"
# define STR_D_GREATER ">>"
# define STR_PIPE "|"
# define STR_SPACE " "

//Std

# define STDIN 0
# define STDOUT 1
# define STDERR 2

/******************************************************************************
 *                               STRUCTURES                                   *
 *****************************************************************************/

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_redirection
{
	char    *str;
	t_mode   mode;
	struct s_redirection *next;
	struct s_redirection *prev;
}   t_redirection;

typedef struct s_command_table
{
	struct s_command    *commands;
	struct s_env        *env;
	pid_t	            pid;
}   t_command_table;

typedef struct s_command
{
	char	*cmd;
	char    *full_cmd;
	char	*path; //"builtin" if its a builtin
	char	**args;
	//char    **options; //NULL it its not a builtin
	//char    **parameters; //NULL if its not a builtin
	t_redirection   *redirection;
	struct s_command *next;
	struct s_command *prev;
}   t_command;

typedef struct s_token
{
	char    *token;
	char    *trimmed_token;
	char    *expanded_token;
	t_type     type;
	int         to_expand;
	struct s_token *next;
	struct s_token *prev;
}   t_token;

/******************************************************************************
 *                            GLOBAL VARIABLE                                 *
 *****************************************************************************/

//int g_exit_status;

/******************************************************************************
 *                               FUNCTIONS                                    *
 *****************************************************************************/

//testmain.c


//main_parser.c
t_command *main_parser(char *str, t_env *envlist);

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

//expander.c
int there_is_a_dollar(char *str);
void    analyze_tokens_to_expand(t_token *list);
void    expand_tokens(t_token *list, t_env *envlist);

//trim_tokens.c
void    trim_tokens(t_token *list);

//parser.c
t_command   *convert_tokens_to_commands(t_token *list, t_env *envlist);

//commands_handler.c
void    print_command(t_command *node);
void    add_command(t_token *list, t_command *first);
t_command *create_command(t_token *list);

//check_tokens.c
void    check_tokens(t_token *list);

//redirections.c
void    add_redirection(t_token *list, t_redirection *first);
t_redirection *create_redirection(t_token *list);

//exec_utils.c
t_env	*ft_list_env(char **envp); //pour dupliquer env au début du prog
t_env	*ft_new_var(char *keyvalue);
void	ft_lstaddback(t_env **alst, t_env *new);
void	ft_clean_list(t_env	*envlist);

//builtins
char    *ft_getenv(char *key, t_env *envlist); //pour expander
int ft_cd(char **params, t_env *envlist);
int ft_env(char **params, t_env *envlist);

//get_path.c
char    *get_command_path(char *command, t_env *envlist);
char    *environment_path(char *command, char *path_var);
char	*absolute_relative_path(char *command);
void	ft_free_tab(char **tab);

#endif
