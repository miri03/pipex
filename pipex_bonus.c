/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:16:57 by meharit           #+#    #+#             */
/*   Updated: 2023/02/10 00:46:43 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	child_proc(t_var *var, char **argv, char **envp, int cmd)
{
	if (var->fd0 ==  -1)
		exit (0);
	var->command = does_exist(argv[cmd], var);
	if (var->command == NULL)
	{
		ft_putstr_fd("command not found\n", 1);
		exit(127);
	}
	if (dup2(var->fd0, 0) == -1)
		perror("dup2 fd0");
	if (dup2(var->pipe[1], 1) == -1)
		perror(":");
	close(var->pipe[0]);
	close(var->fd1);
	if (execve(var->command, var->com_p, envp) == -1)
		perror("var->command");
	// write output of cmd1 in pipe[1] 
}

void	child_proc2(t_var *var, char **argv, char **envp, int cmd)
{
	if (var->fd1 ==  -1)
		exit (1);
	var->command = does_exist(argv[cmd], var);
	if (var->command == NULL)
	{
		ft_putstr_fd("command not found\n", 1);
		exit(127);
	}
	if (dup2(var->pipe[1], 1) == -1)
		perror("dup2 fd1");
	if (dup2(var->pipe[0], 0) == -1)
		perror(":");
	close(var->pipe[1]);
	close(var->fd0);
	if (execve(var->command, var->com_p, envp) == -1)
		perror(var->command);
	exit(126);
	// read output from pipe[0] 
}


int main(int argc, char **argv, char **envp)
{
	int		i;
	int		cmd;
	t_var	var;
	int		fk;
	
	i = 0;
	cmd = 2;
	var.fd0 = open(argv[1], O_RDONLY);
	var.fd1 = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	fk = fork();
	while (i < argc - 2)
	{
		if (pipe(var.pipe) == -1)
			perror("pipe");
		if (fk == 0)
			child_proc(&var, argv, envp, cmd);
		fk = fork();
		cmd++;
		if (fk == 0)
			child_proc2(&var, argv, envp, cmd);

		
