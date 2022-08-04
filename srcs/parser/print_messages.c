#include "minishell.h"

int print_errors(int error)
{
    if (error == QUOTES_ERROR)
        printf(QUOTES_ERR_MSSG);
    if (error == TOKENS_ERROR)
        printf(TOKENS_ERR_MSSG);
    return(error);
}
