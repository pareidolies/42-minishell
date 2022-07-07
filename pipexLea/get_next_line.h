/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:32:24 by lmurtin           #+#    #+#             */
/*   Updated: 2022/06/24 23:32:25 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

typedef struct s_reads
{
	char			*content;
	int				count;
	int				nb_read;
	int				iter;
	struct s_reads	*next;
}			t_reads;
char	*get_next_line(int fd);
int		ft_read(int fd, t_reads *head, t_reads *node);
t_reads	*ft_lastnode(t_reads *head, t_reads *node);
t_reads	*ft_addnew_back(t_reads *head, t_reads *curr, char *buffer, int nread);
int		ft_find_eol(t_reads *node);
char	*ft_extract(t_reads *head, int count);
int		ft_process_node(char **str, int i, t_reads *node);
void	ft_clean(t_reads *head, int count, int clear);

#endif