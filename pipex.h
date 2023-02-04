/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:38:08 by meharit           #+#    #+#             */
/*   Updated: 2023/02/04 23:40:57 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

typedef struct s_var
{
	int	pipe[2];
	int	fd0;
	int	fd1;
	char	**path;
	char	*command;
	char	**com_p;
}			t_var;

void	ft_putstr_fd(char *s, int fd);
void	error_message(char *error);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**get_path(char **envp);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
void	check_commande(char *path_c, char **path);
char	*does_exist(char *comm, t_var *var);
#endif
