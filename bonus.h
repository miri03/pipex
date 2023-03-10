/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 23:32:24 by meharit           #+#    #+#             */
/*   Updated: 2023/02/16 16:36:20 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdbool.h>
# include "get_next_line.h"

typedef struct s_var
{
	int		**pipe;
	int		fd0;
	int		fd1;
	char	**path;
	char	*command;
	char	**com_p;
	int		fd_r;
}			t_var;

char	*get_next_line(int fd);
int		ft_strcmp(char *s1, char *s2);
void	uti_child1(t_var *var, int i);
void	child_proc(t_var *var, char **envp, char *cmd, int i);
void	child_proc2(t_var *var, char **envp, char *cmd, int i);
void	ft_putstr_fd(char *s, int fd);
void	error_message(char *error);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**get_path(char **envp);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2, int f);
void	check_commande(char *path_c, char **path);
char	*does_exist(char *comm, t_var *var);
void	here_doc(int argc, char **argv, char **envp);
int		ft_strlen(const char *s);
void	make_pipes(t_var *var, int n_pipe);
int		parent_proc(t_var *var, int *frk, int i);

#endif
