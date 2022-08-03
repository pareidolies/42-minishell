#include "minishell.h"

int print_errors(int error)
{
    if (error == QUOTES_ERROR)
        printf(QUOTES_ERR_MSSG);

    return(error);
}
