/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:21:39 by meharit           #+#    #+#             */
/*   Updated: 2023/02/16 00:58:44 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

void	uti_child1(t_var *var, int i)
{
	if (i > 0)
	{
		close(var->fd0);
		close(var->pipe[i - 1][1]);
	}
	close(var->pipe[i][0]);
	if (var->fd0 == -1)
		exit (0);
}

void	child_proc(t_var *var, char **envp, char *cmd, int i)
{
	uti_child1(var, i);
	var->command = does_exist(cmd, var);
	
	if (var->command == NULL)
	{
		ft_putstr_fd("command not found\n", 1);
		exit(127);
	}
	if (i == 0)
	{
		if (dup2(var->fd0, 0) == -1)
			perror("dup2 fd0");
	}
	else
	{
		if (dup2(var->pipe[i - 1][0], 0) == -1)
			perror("dup2 pipe");
	}
	printf("%d %d\n", var->pipe[i][0], var->pipe[i][1]);
	// if (dup2(var->pipe[i][1], 1) == -1)
	// 	perror(":");
	
	close(var->fd1);
	if (execve(var->command, var->com_p, envp) == -1)
		perror("var->command");
}

void	child_proc2(t_var *var, char **envp, char *cmd, int i)
{
	close(var->pipe[i - 1][1]);
	if (var->fd1 == -1)
		exit (1);
	var->command = does_exist(cmd, var);
	if (var->command == NULL)
	{
		ft_putstr_fd("command not found\n", 1);
		exit(127);
	}
	
	if (dup2(var->fd1, 1) == -1)
		perror("dup2 fd1");
	if (dup2(var->pipe[i - 1][0], 0) == -1)
		perror("dup2 last pipe");
	close(var->pipe[i - 1][0]);
	printf("ok1\n");
	if (execve(var->command, var->com_p, envp) == -1)
		perror(var->command);
	exit(126);
}
