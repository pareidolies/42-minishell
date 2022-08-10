/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:34:45 by lmurtin           #+#    #+#             */
/*   Updated: 2022/08/10 12:44:08 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

extern int	g_exit_status;

char	*replace_str(char **str, char *buf)
{
	char	*tmp;

	tmp = ft_strjoin(*str, buf);
	magic_malloc(ADD, 0, tmp);
	magic_malloc(FREE, 0, *str);
	return (tmp);
}

static void	ft_read(int fd, char *buf, char **str)
{
	int		r;
	char	*tmp;

	if (!*str || !ft_strchr(*str, '\n'))
	{
		r = read(fd, buf, BUFFER_SIZE);
		while (r > 0)
		{
			buf[r] = '\0';
			if (!*str)
			{
				*str = ft_substr(buf, 0, r);
				magic_malloc(ADD, 0, *str);
			}
			else
			{
				tmp = replace_str(str, buf);
				*str = tmp;
			}
			if (ft_strchr(buf, '\n'))
				break ;
			r = read(fd, buf, BUFFER_SIZE);
		}
	}
	magic_malloc(FREE, 0, buf);
}

static char	*ft_returnline(char **str)
{
	int		end;
	int		n;
	char	*ret;
	char	*tmp;

	if (!ft_strchr(*str, '\n'))
	{
		ret = ft_substr(*str, 0, ft_strlen(*str));
		magic_malloc(ADD, 0, ret);
		magic_malloc(FREE, 0, *str);
		*str = NULL;
		return (ret);
	}
	end = ft_strlen(*str);
	n = ft_strlen(ft_strchr(*str, '\n'));
	ret = ft_substr(*str, 0, end - n + 1);
	magic_malloc(ADD, 0, ret);
	tmp = ft_substr(ft_strchr(*str, '\n'), 1, n - 1);
	magic_malloc(ADD, 0, tmp);
	magic_malloc(FREE, 0, *str);
	*str = tmp;
	return (ret);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*str;

	buf = magic_malloc(MALLOC, sizeof(char) * (BUFFER_SIZE + 1), NULL);
	if (BUFFER_SIZE < 1 || fd < 0 || read(fd, buf, 0) < 0)
	{
		magic_malloc(FREE, 0, buf);
		return (NULL);
	}
	ft_read(fd, buf, &str);
	if (str == NULL || str[0] == '\0')
	{
		magic_malloc(FREE, 0, str);
		str = NULL;
		return (NULL);
	}
	return (ft_returnline(&str));
}
