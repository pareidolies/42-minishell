#ifndef MINISHELL_H

# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <signal.h>

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

//Ascii Art

# define L10 "▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫\n"
# define L0 "▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪\n"
# define L1 "           _.---._                                     _          _ _      \n"  
# define L2 "       .\'\"\".'/|\\`.\"\"\'.         _ __ ___  _ _ __  _ ___| |__   ___| | |     \n" 
# define L3 "      :  .' / | \\ `.  :	      | '_ ` _ \\| | '_ \\| / __| '_ \\ / _ \\ | |	   \n"  
# define L4 "      '.'  /  |  \\  `.'       | | | | | | | | | | \\__ \\ | | |  __/ | |     \n"  
# define L5 "       `. /   |   \\ .'        |_| |_| |_|_|_| |_|_|___/_| |_|\\___|_|_|     \n" 
# define L6 "         `-.__|__.-'                                                       \n\n" 
# define L7 "					     	  		 Welcome   ° .	\n"
# define L8 "             				   				   ° <><    \n"
# define L9 "▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪▪\n\n"
# define L19 "▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫▫\n"
# define L20 ".....................................................................................\n"
# define L21 "--------------------------------------------------------------------------------------\n"
# define L22 "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
# define L23 "**************************************************************************************\n"
# define L24 "______________________________________________________________________________________\n\n"  
# define L44 "   	°  o   ◯  .			\n\n"  
# define L45 "     				° O   .			\n\n"  

//Colors

# define ANSI_COLOR_BLUE		"\x1b[94m"
# define ANSI_COLOR_LIGHT_YELLOW		"\x1b[93m"
# define ANSI_COLOR_ORANGE		"\e[1;31m"
# define ANSI_COLOR_LIGHT_WHITE		"\x1b[97m"
# define ANSI_COLOR_LIGHT_RED		"\x1b[91m"
# define ANSI_COLOR_REG_RED	"\e[0;31m"
# define ANSI_COLOR_BOLD_RED	"\e[1;31m"
# define ANSI_COLOR_RESET		"\x1b[0m"
# define ANSI_COLOR_YELLOW	"\033[93m"
# define ANSI_COLOR_CYAN	"\e[0;36m"
# define ANSI_COLOR_GREEN	"\e[0;32m"
# define ANSI_COLOR_BOLD_CYAN	"\e[1;36m"

//Characters

# define S_QUOTE '\''
# define D_QUOTE '"'
# define SPACE ' '
# define LESS '<'
# define GREATER '>'
# define PIPE '|'
# define DOLLAR '$'
# define QUESTION '?'

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

//Malloc

# define FREE 4242
# define MALLOC 4343
# define ADD 4444
# define QUIT 0 //A CHANGER

//GNL

# define BUFFER_SIZE 10

//Errors

# define QUOTES_ERROR 1
# define TOKENS_ERROR 2
# define MALLOC_ERROR 3

//Error messages

# define QUOTES_ERR_MSSG "error: wrong number of quotes\n"
# define TOKENS_ERR_MSSG "error: wrong number of redirections or pipes\n"
# define HEREDOC_ERR_MSSG "warning: here-document delimited by end-of-file wanted "
# define MALLOC_ERR_MSSG "error: a malloc error occured\n"

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
	char	*str;
	t_mode	mode;
	int		fd;
	struct s_redirection *next;
	struct s_redirection *prev;
}   t_redirection;

typedef struct s_data
{
	struct s_command    *commands;
	struct s_env        *envlist;
	int					nb_fd_pipes;
	int					nb_pid;
	int					std_in;
	int					std_out;
	int					*pipes;
	pid_t	            *pid;
}   t_data;

typedef struct s_command
{
	char	*cmd;
	char    *full_cmd;
	char	*path; //"builtin" if its a builtin
	char	**args;
	int		index;
	t_redirection   *redirection;
	struct s_command *next;
	struct s_command *prev;
}   t_command;

typedef struct s_token
{
	char    *token;
	char    *expanded_token;
	t_type     type;
	int         to_expand;
	struct s_token *next;
	struct s_token *prev;
}   t_token;

typedef struct s_malloc
{
	void			*addr;
	struct s_malloc	*next;
	struct s_malloc	*prev;
}	t_malloc;

typedef struct s_quotes_nbr
{
	int	simple_q;
	int	double_q;
}	t_quotes_nbr;

/******************************************************************************
 *                            GLOBAL VARIABLE                                 *
 *****************************************************************************/

extern int g_exit_status;

/******************************************************************************
 *                               FUNCTIONS                                    *
 *****************************************************************************/

//testmain.c
void	set_line(void);

//main_parser.c
t_command	*parse_input(char *str, t_env *envlist);

//token_handler.c
void	print_tokens(t_token *token);
void	add_token(t_token *list, char *str, int flag);
t_token	*create_token(char *str, int flag);

//tokenization.c
int		check_quotes(char *str);
int		get_token_size(char *str);
t_token	*convert_input_to_tokens(char *str);
void	analyze_tokens_type(t_token *list);
void	analyze_literals_type(t_token *list);

//expander.c
void	expander(t_token *list, t_env *envlist);

//trim_tokens.c
void	trim_tokens(t_token *list);
char	*withdraw_quotes(char   *str);

//parser.c
t_command	*convert_tokens_to_commands(t_token *list, t_env *envlist);

//commands_handler.c
void		print_command(t_command *node);
void		add_command(t_token *list, t_command *first);
t_command	*create_command(t_token *list);

//check_tokens.c
int	check_tokens(t_token *list);

//quotes_utils.c
int	calculate_result(int result, char c);
int	is_in_quote(char *str, int pos);
int	is_in_d_quote(char *str, int pos);
int	is_in_s_quote(char *str, int pos);

//expander_utils.c
int	get_expansion_start(char *str, char *initial, int pos);
int	get_expansion_size(char *str);

//redirections.c
void			add_redirection(t_token *list, t_redirection *first);
t_redirection	*create_redirection(t_token *list);

//tokens_utils.c
int	is_pipe_or_redir_or_quote(char c);
int	is_d_redir(char *str);
int	is_s_redir(char c);

//free_tokens.c
void	free_tokens(t_token *list);
void	free_commands(t_command *list);

//magic_malloc.c
void	*magic_malloc(int choice, size_t size, void *addr);

//split_parser.c
int		is_in_quote(char *str, int pos);
char	**split_parser(char *str, char c);

//exec_utils.c
t_env	*ft_list_env(char **envp); //pour dupliquer env au début du prog
t_env	*ft_new_var(char *keyvalue);
void	ft_lstaddback(t_env **alst, t_env *new);
void	ft_clean_list(t_env	*envlist);

//builtins
char	*ft_getenv(char *key, t_env *envlist);
int		update_env(char *key, char *newvalue, t_env	*envlist);
void	ft_delenv(t_env *var, t_env *envlist);
t_env	*ft_new_var_split(char *key, char *value);
t_env	*ft_getenv_var(char *key, t_env *envlist);
int		nb_param(char **params);
int		ft_cd(char **params, t_env *envlist);
int		cd_others(char **params, t_env *envlist);
int		ft_echo(char **params);
int		ft_env(char **params, t_env *envlist);
int		ft_export(char **params, t_env *envlist);
int		export_checks(char **params);
char	*export_find_name(char *str);
int		valid_identifier(char *name);
int		ft_unset(char **params, t_env *envlist);
int		ft_pwd(char **params);
int		ft_exit(char **params, t_env *envlist);


//get_path.c
char	*get_command_path(char *command, t_env *envlist);
char	*environment_path(char *command, char *path_var);
char	*absolute_relative_path(char *command);
void	ft_free_tab(char **tab);

//ft_exec.c
int 	ft_exec(t_command *commands, t_env *envlist);
t_data	*ft_init_data(t_command *commands, t_env *envlist);
int		exec_no_pipeline(t_data *mini, t_command *current_cmd, t_env *envlist);
int		which_builtin(char **args, t_env *envlist);

//ft_fork.c
pid_t   *multi_fork(t_data *mini);
pid_t   ft_fork(t_data *mini, t_command *cmd);

//ft_heredoc.c
int		ft_heredoc(t_data *mini);
int		open_heretmp(t_command *cmd, int flag);
void	ft_tempfile(char *str, int fd, int fdtmp);

//gnl.c
char	*get_next_line(int fd);

//redir_and_pipes.c
int redir_open(t_command *current_cmd, int fd[2]);
int redir_close(t_data *mini, t_command *current_cmd, int flag);
int	*open_pipes(t_data *mini);
int	ft_close_all(int *fd, int nb);

//handle_fd.c
int	dup_close_in(t_data *mini, t_command *current_cmd, int fd[2]);
int	dup_close_out(t_data *mini, t_command *current_cmd, int fd[2]);

//child.c
int		ft_child(t_data *mini, t_command *cmd, t_env *envlist);
char	**ft_convertlist(t_env *envlist);

//print_messages.c
int print_errors(int error);
void	ft_putstr_fd_color(char *str, int fd, char *color);

//error.c
int	ft_update_status(int code, t_env *envlist);

//say_hello.c
void    say_hello(void);

//signals.c
int	set_signals_as_prompt(void);
int	set_signals_as_here_doc(void);
void	signal_handler_as_prompt(int signum);
void	signal_handler_as_here_doc(int signum);

#endif
