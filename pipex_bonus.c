/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:16:57 by meharit           #+#    #+#             */
/*   Updated: 2023/02/11 23:51:59 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"
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
	//if (dup2(var->pipe[1], 1) == -1)
	//	perror(":");
	var->fd_r = var->pipe[0];
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
	if (dup2(var->fd1, 1) == -1)
		perror("dup2 fd1");
	if (dup2(var->pipe[0], 0) == -1) // diff proc 
		perror(":");
	close(var->pipe[1]);
	close(var->fd0);
	if (execve(var->command, var->com_p, envp) == -1)
		perror(var->command);
	exit(126);
	// read output from pipe[0] 
}

int	parent_proc(t_var *var, int *frk)
{
	int	status;
	int	st;

	close(var->fd0);
	close(var->fd1);
	close(var->pipe[0]);
	close(var->pipe[1]);
	waitpid(frk[0], &status, 0);
	waitpid(frk[1], &st, 0);
	if (WIFEXITED(st) == true)
	{
		if (WEXITSTATUS(st))
			return (WEXITSTATUS(st));
	}
	return (1);
}

int main(int argc, char **argv, char **envp)
{
	t_var	var;
	int		i;
	int		cmd;
	int		status;
	int		*fk;

	if (argc < 5)
		error_message("Not enought/too much arguments\n");
	status = 0;
	fk = malloc(sizeof(int) * (argc - 2));
	i = 1;
	cmd = 2;
	var.fd0 = open(argv[1], O_RDONLY);
	var.fd1 = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (var.fd0 == -1)
		perror(argv[1]);
	if (var.fd1 == -1)
		perror(argv[4]);
	var.path = get_path(envp);
	while (i < argc - 2)
	{
		fk[i] = fork();
		if (pipe(var.pipe) == -1)
			perror("pipe");
		if (fk[i] == 0)
			child_proc(&var, argv, envp, cmd);
		cmd++;
		i++;
		//if (fk[argc - 3] == 0)
		//	child_proc2(&var, argv, envp, cmd);
		if (fk[argc - 3]  == 1)
			status = parent_proc(&var, fk);
	}
	return (status);
}
