/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smostefa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:58:07 by smostefa          #+#    #+#             */
/*   Updated: 2022/08/04 12:58:23 by smostefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_errors(int error)
{
	if (error == QUOTES_ERROR)
		printf(QUOTES_ERR_MSSG);
	if (error == TOKENS_ERROR)
		printf(TOKENS_ERR_MSSG);
	return (error);
}
