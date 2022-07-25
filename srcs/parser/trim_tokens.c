#include "minishell.h"

//char	*ft_substr(char const *s, unsigned int start, size_t len)

char    *withdraw_quotes(char   *str)
{
    int     i;
    char    *result;
    int     start;

    printf("STR : %s\n", str);
    result = ft_strdup("");
    i = 0;
    while (str[i])
    {
        start = i;
        if (str[i] == S_QUOTE)
        {
            i++;
            while(str[i] && str[i] != S_QUOTE)
                i++;
            result = ft_strjoin(result, ft_substr(str, start + 1, i - start - 1));
            printf("RES 1 : %s\n", result);
            i++;
        }
        else if (str[i] == D_QUOTE)
        {
            i++;
            while(str[i] && str[i] != D_QUOTE)
                i++;
            result = ft_strjoin(result, ft_substr(str, start + 1, i - start - 1));
            printf("RES 2 : %s\n", result);
            i++;
        }
        else
        {
            while (str[i] && str[i] != S_QUOTE && str[i] != D_QUOTE)
                i++;
            result = ft_strjoin(result, ft_substr(str, start, i - start));
            printf("RES 3 : %s\n", result);
        }
        //i++;
    }
    return (result);
}

void    trim_tokens(t_token *list)
{
    t_token *current;

    current = list;
    while (current != NULL)
    {
        current->trimmed_token = withdraw_quotes(current->expanded_token);
        current = current->next;
    }
}