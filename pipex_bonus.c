/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:16:57 by meharit           #+#    #+#             */
/*   Updated: 2023/02/13 13:45:52 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

void	child_proc(t_var *var, char **argv, char **envp, int cmd, int i)
{
	if (i > 0)
	{
		close(var->fd0);
		close(var->pipe[i - 1][1]);
	}
	close(var->pipe[i][0]);
	if (var->fd0 == -1)
		exit (0);
	var->command = does_exist(argv[cmd], var);
	if (var->command == NULL)
	{
		ft_putstr_fd("command not found0\n", 1);
		exit(127);
	}
	printf("child1\n");
	if (i == 0)
	{
		if (dup2(var->fd0, 0) == -1) 
			perror("dup2 fd0");
	}
	else
	{
		if (dup2(var->pipe[i - 1][0], 0) == -1)
			perror("dup2 fd0");
	}
	if (dup2(var->pipe[i][1], 1) == -1)
		perror(":");
	close(var->fd1);
	printf("child12\n");
	if (execve(var->command, var->com_p, envp) == -1)
		perror("var->command");
	// write output of cmd1 in pipe[1] 
}

void	child_proc2(t_var *var, char **argv, char **envp, int cmd, int i)
{
	printf("child2\n");
	if (var->fd1 ==  -1)
	{
		printf("here fd1 \n");
		exit (1);
	}
	var->command = does_exist(argv[cmd], var);
	if (var->command == NULL)
	{
		ft_putstr_fd("command not found1\n", 1);
		exit(127);
	}
	if (dup2(var->fd1, 1) == -1)
		perror("dup2 fd1");
	if (dup2(var->pipe[i - 1][0], 0) == -1)
		perror(":");
	close(var->pipe[i - 1][1]);
	close(var->fd0);
	if (execve(var->command, var->com_p, envp) == -1)
		perror(var->command);
	exit(126);
	// read output from pipe[0] 
}

int	parent_proc(t_var *var, int *frk, int i)
{
	//(void) frk; //////
	int	status;
	int	w;

	w = 0;
	close(var->fd0);
	close(var->fd1);
	while (w < i - 1)
	{
		close(var->pipe[w][0]);
		close(var->pipe[w][1]);
		w++;
	}
	w = 0;
	printf("i-1 =>%d\n", i-1);
	while (w < i - 2)
	{
		waitpid(frk[w], NULL, 0);
		w++;
	}
	printf("====> done waiting2\n");
	waitpid(frk[i-1], &status, 0);
	printf("====> done waiting\n");
	
	if (WIFEXITED(status) == true)
	{
		if (WEXITSTATUS(status))
			return (WEXITSTATUS(status));
	}
	printf("here\n");
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
	var.pipe = malloc(sizeof(int*) * (argc - 4));
	fk = malloc(sizeof(int) * (argc - 3));
	i = 0;
	cmd = 2;
	var.fd0 = open(argv[1], O_RDONLY);
	var.fd1 = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (var.fd0 == -1)
		perror(argv[1]);
	if (var.fd1 == -1)
		perror(argv[argc - 1]);
	var.path = get_path(envp);
	while (i < argc - 3)
	{
		if(i < argc - 4)
		{
			var.pipe[i] = malloc(sizeof(int) * 2);
			if (pipe(var.pipe[i]) == -1)
				perror("pipe");
		}
		fk[i] = fork();
		if (i < argc - 4 && fk[i] == 0)
			child_proc(&var, argv, envp, cmd, i);
		if (i == argc - 4 && fk[i] == 0)
			child_proc2(&var, argv, envp, cmd, i);
		cmd++;
		i++;
	}
	printf("%d\n", fk[i - 1]);
	status = parent_proc(&var, fk, i);
	return (status);
}
