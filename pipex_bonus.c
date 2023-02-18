/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:16:57 by meharit           #+#    #+#             */
/*   Updated: 2023/02/18 16:46:57 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

int	parent_proc(t_var *var, int *frk, int i)
{
	int	status;
	int	w;

	w = 0;
	close(var->fd1);
	close(var->fd0);
	while (w < i - 1)
	{
		close(var->pipe[w][0]);
		close(var->pipe[w][1]);
		w++;
	}
	w = 0;
	while (w < i - 1)
	{
		waitpid(frk[w], NULL, 0);
		w++;
	}
	waitpid(frk[w], &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

void	make_pipes(t_var *var, int n_pipe)
{
	static int	j;

	while (j < n_pipe)
	{
		var->pipe[j] = (int *)malloc(sizeof(int) * 2);
		if (pipe(var->pipe[j]) == -1)
			perror("pipe");
		j++;
	}
}

int	uti_parent(t_var *var, int argc, char **envp, char **argv)
{
	int			status;
	static int	i;
	int			cmd;
	int			*frk;

	cmd = 2;
	frk = malloc(sizeof(int) * (argc - 3));
	while (i < argc - 3)
	{
		make_pipes(var, argc - 4);
		frk[i] = fork();
		if (i < argc - 4 && frk[i] == 0)
			child_proc(var, envp, argv[cmd], i);
		if (i < argc - 4)
			close(var->pipe[i][1]);
		if (i)
			close(var->fd0);
		if (i == argc - 4 && frk[i] == 0)
			child_proc2(var, envp, argv[cmd], i);
		cmd++;
		i++;
	}
	free(frk);
	status = parent_proc(var, frk, i);
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	t_var	var;
	int		status;

	if (argc < 5)
		error_message("Not enought/too much arguments\n");
	if (ft_strcmp(argv[1], "here_doc") == 0)
		here_doc(argc, argv, envp);
	status = 0;
	var.pipe = (int **)malloc(sizeof(int *) * (argc - 4));
	var.fd0 = open(argv[1], O_RDONLY);
	var.fd1 = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (var.fd0 == -1)
		perror(argv[1]);
	if (var.fd1 == -1)
		perror(argv[argc - 1]);
	var.path = get_path(envp);
	status = uti_parent(&var, argc, envp, argv);
	return (status);
}
