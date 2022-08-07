#include "minishell.h"

extern int g_exit_status;

int	set_signals_as_prompt(void)
{
	signal(SIGINT, signal_handler_as_prompt);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}

int	set_signals_as_here_doc(void)
{
	return (1);
}

void	signal_handler_as_prompt(int signum)
{
	if (signum == SIGINT)
    {
		ft_putstr_fd("\nminishell>> ", 1);
        g_exit_status = 1;
    }
}

void	signal_handler_as_here_doc(int signum)
{
    (void) signum;
	;
}