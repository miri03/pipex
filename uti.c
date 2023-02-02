/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:48:33 by meharit           #+#    #+#             */
/*   Updated: 2023/02/02 21:27:55 by meharit          ###   ########.fr       */
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

char	*does_exist(char *path_c, char **path)
{
	int		i;
	char	*test;
	char	**command;
	i = 0;

	command = ft_split(path_c, ' ');
	if (access(command[0], F_OK) == 0)
		return (command[0]);
	command[0] = ft_strjoin("/", command[0]);
	while (path[i])
	{
		test = ft_strjoin(path[i], command[0]);
		if (access(test, F_OK) == 0)
			return (test);
		i++;
	}
	return (NULL);
}

void	check_commande(char *path_c, char **path)
{
	char	*pat;
	
	pat = does_exist(path_c, path);
	printf("%s\n", pat);

}
