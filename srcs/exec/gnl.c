#include "minishell.h"
#include "libft.h"

static void	ft_read(int fd, char *buf, char **str)
{
	int		r;
	char	*tmp;

	//printf("in ft_read\n");
	if (!*str || !ft_strchr(*str, '\n'))
	{
		r = read(fd, buf, BUFFER_SIZE);
		while (r > 0)
		{
			buf[r] = '\0';
			if (!*str)
				*str = ft_substr(buf, 0, r);
			else
			{
				tmp = ft_strjoin(*str, buf);
				magic_malloc(FREE, 0, *str);
				//free(*str);
				*str = tmp;
			}
			if (ft_strchr(buf, '\n'))
				break ;
			r = read(fd, buf, BUFFER_SIZE);
		}
	}
	free(buf);
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
		free(*str);
		*str = NULL;
		return (ret);
	}
	end = ft_strlen(*str);
	n = ft_strlen(ft_strchr(*str, '\n'));
	ret = ft_substr(*str, 0, end - n + 1);
	tmp = ft_substr(ft_strchr(*str, '\n'), 1, n - 1);
	magic_malloc(ADD, 0, tmp); //
	free(*str);
	*str = tmp;
	return (ret);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*str;

	// if (flag == 1 && str != NULL)
	// {
	// 	free(str);
	// 	return (NULL);
	// }
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	//printf("str = [%s]\n", str);
	if (BUFFER_SIZE < 1 || fd < 0 || read(fd, buf, 0) < 0)
	{
		//printf("coucou\n");
		free(buf);
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
