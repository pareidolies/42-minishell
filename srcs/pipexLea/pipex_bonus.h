/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmurtin <lmurtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:50:19 by lmurtin           #+#    #+#             */
/*   Updated: 2022/06/27 22:53:40 by lmurtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	int		*fd;
	int		*pid;
	int		nbfd;
	int		nbpid;
	int		index;
	int		here;
	char	*limiter;
}			t_data;

/*Pipes*/
int		*ft_open_pipes(int n);

/*Heredoc*/
int		ft_heredoc(char *limiter, t_data *pipex);
void	ft_tempfile(char *limiter, int fd, int fdtmp);
int		ft_child_first2(char **argv, char **envp, t_data *pipex);
int		ft_child_last2(char **argv, char **envp, t_data *pipex);

/*Child processes*/
int		ft_fork(char **argv, char **envp, t_data *pipex);
int		ft_fork_f(char **argv, char **envp, t_data *pipex);
int		ft_fork_l(char **argv, char **envp, t_data *pipex);
int		ft_child(char **argv, char **envp, t_data *pipex);
int		ft_child_first(char **argv, char **envp, t_data *pipex);
int		ft_child_last(char **argv, char **envp, t_data *pipex);

/*Finding the command path and checking the access to the binary*/
char	*ft_get_path(char *cmd, char **envp);
char	*ft_env_path(char *cmd, char **envp);
char	*ft_check_path(char *pathline, char *cmd);

/*Utilitaries*/
t_data	*ft_init(int argc, char **argv);
int		ft_close_all(int *fd, int size);
void	ft_full_free(t_data *pipex, int flag);
void	ft_free(char **tab);

#endif
