/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:48:33 by meharit           #+#    #+#             */
/*   Updated: 2023/02/15 18:44:14 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_message(char *error)
{
	ft_putstr_fd(error, 2);
	exit (1);
}

char	*the_path(char **envp)
{
	int	j;

	j = 0;
	while (envp[j])
	{
		if (!ft_strncmp(envp[j], "PATH=", 5))
			return (&envp[j][5]);
		j++;
	}
	return (NULL);
}

char	**get_path(char **envp)
{
	char	*pth;
	char	**path;

	pth = the_path(envp);
	path = ft_split(pth, ':');
	return (path);
}

char	*does_exist(char *comm, t_var *var)
{
	int		i;
	char	*test;

	i = 0;
	var->com_p = ft_split(comm, ' ');
	if (access(var->com_p[0], F_OK) == 0)
		return (var->com_p[0]);
	var->com_p[0] = ft_strjoin("/", var->com_p[0], 1);
	if (var->path)
	{
		while (var->path[i])
		{
			test = ft_strjoin(var->path[i], var->com_p[0], 0);
			if (access(test, F_OK) == 0)
				return (test);
			free(test);
			i++;
		}
	}
	free(var->com_p[0]); //?
	return (NULL);
}
