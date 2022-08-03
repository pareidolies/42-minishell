#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 10
// get_next_line.c
char	*get_next_line(int fd);

// get_next_line_utils.c
// char	*ft_strchr(const char *s, int c);
// char	*ft_substr(const char *s, unsigned int start, size_t len);
// size_t	ft_strlen(const char *s);
// char	*ft_strjoin(const char *s1, const char *s2);

#endif

// #ifndef GET_NEXT_LINE_H
// # define GET_NEXT_LINE_H

// typedef struct s_reads
// {
// 	char			*content;
// 	int				count;
// 	int				nb_read;
// 	int				iter;
// 	struct s_reads	*next;
// }			t_reads;
// char	*get_next_line(int fd);
// int		ft_read(int fd, t_reads *head, t_reads *node);
// t_reads	*ft_lastnode(t_reads *head, t_reads *node);
// t_reads	*ft_addnew_back(t_reads *head, t_reads *curr, char *buffer, int nread);
// int		ft_find_eol(t_reads *node);
// char	*ft_extract(t_reads *head, int count);
// int		ft_process_node(char **str, int i, t_reads *node);
// void	ft_clean(t_reads *head, int count, int clear);

// #endif