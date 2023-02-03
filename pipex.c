/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:37:32 by meharit           #+#    #+#             */
/*   Updated: 2023/02/03 18:51:04 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>

void	child_proc(t_var *var, char **argv, char **envp)
{
	var->command = does_exist(argv[2], var);
	close(0);
	if (dup2(var->fd0, 0) == -1)
		perror("dup2 fd0");
	if (dup2(var->pipe[1], 1) == -1)
		perror("dup2 pipe[1]");
	close(var->pipe[0]);
	close(var->fd1);
	if (execve(var->command, var->com_p, envp) == -1)
	{
		printf("ok\n");
		perror("execve");
	}
	// write output of cmd1 in pipe[1] 
}

void	parent_proc(t_var *var, char **argv, char **envp)
{
	var->command = does_exist(argv[3], var);
	// close(1);
	if (dup2(var->fd1, 1) == -1)
		perror("dup2 fd1");
	if (dup2(var->pipe[0], 0) == -1)
		perror("dup2 pipe[0]");
	close(var->pipe[1]);
	close(var->fd0);
	if (execve(var->command, var->com_p, envp) == -1)
	{
		printf("ok\n");
		perror("execve");
	}


	// write output of cmd1 in pipe[1] 
}
int main(int argc, char **argv, char **envp)
{
	t_var	var;
	int		frk[2];

	if (argc != 5)
		error_message("Not enought/too much arguments\n");
	var.fd0 = open(argv[1], O_RDONLY);
	var.fd1 = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (var.fd1 == -1)
	{
		printf("fd0\n");
		perror(argv[4]);
	}
	if (var.fd0 == -1)
	{
		printf("fd0\n");
		perror(argv[1]);
		var.fd0 = open("/tmp/temp_file", O_CREAT);
	}
	var.path = get_path(envp);
	if (pipe(var.pipe) == -1)
		perror("pipe");
	frk[0] = fork();
	if (frk[0] == 0)
		child_proc(&var, argv, envp);
	if (frk[0])
	{
		frk[1] = fork();
		if (frk[1] == 0)
			parent_proc(&var, argv, envp);
		if (frk[1])
		{

			close(var.fd0);
			close(var.fd1);
		}

	}
//	does_exist(char *path_c, char **path)
}
