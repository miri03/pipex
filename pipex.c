/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:37:32 by meharit           #+#    #+#             */
/*   Updated: 2023/02/16 00:22:20 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_proc(t_var *var, char **argv, char **envp)
{
	if (var->fd0 == -1)
		exit (0);
	var->command = does_exist(argv[2], var);
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
}

void	sec_child(t_var *var, char **argv, char **envp)
{
	if (var->fd1 == -1)
		exit (1);
	var->command = does_exist(argv[3], var);
	if (var->command == NULL)
	{
		ft_putstr_fd("command not found\n", 1);
		exit(127);
	}
	if (dup2(var->fd1, 1) == -1)
		perror("dup2 fd1");
	if (dup2(var->pipe[0], 0) == -1)
		perror(":");
	close(var->pipe[1]);
	close(var->fd0);
	if (execve(var->command, var->com_p, envp) == -1)
		perror(var->command);
	exit(126);
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
		return (WEXITSTATUS(st));
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_var	var;
	int		frk[2];
	int		status;

	status = 0;
	if (argc != 5)
		error_message("Not enought/too much arguments\n");
	var.fd0 = open(argv[1], O_RDONLY);
	var.fd1 = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (var.fd0 == -1)
		perror(argv[1]);
	if (var.fd1 == -1)
		perror(argv[4]);
	var.path = get_path(envp);
	if (pipe(var.pipe) == -1)
		perror("pipe");
	frk[0] = fork();
	if (frk[0] == 0)
		child_proc(&var, argv, envp);
	frk[1] = fork();
	if (frk[1] == 0)
		sec_child(&var, argv, envp);
	if (frk[1])
		status = parent_proc(&var, frk);
	return (status);
}
