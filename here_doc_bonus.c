/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:05:33 by meharit           #+#    #+#             */
/*   Updated: 2023/02/16 21:14:52 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

void	put_in_tmp(int fd, char *lim)
{
	char	*line;
	ft_putstr_fd("here_doc> ", 1);
	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, lim, ft_strlen(line)-1) == 0)
			break;
		ft_putstr_fd("here_doc> ", 1);
		write(fd, line, ft_strlen(line));
		line = get_next_line(0);
	}
}

int	hdoc_uti_parent(t_var *var, int argc, char **envp, char **argv)
{
	int			status;
	static int	i;
	int			cmd;
	int			*frk;

	cmd = 3;
	frk = malloc(sizeof(int) * (argc - 4));
	while (i < argc - 4)
	{
		make_pipes(var, argc - 5);
		frk[i] = fork();
		if (i < argc - 5 && frk[i] == 0)
			child_proc(var, envp, argv[cmd], i);
		if (i < argc - 5)
			close(var->pipe[i][1]);
		if (i)
			close(var->fd0);
		if (i == argc - 5 && frk[i] == 0)
			child_proc2(var, envp, argv[cmd], i);
		cmd++;
		i++;
	}
	status = parent_proc(var, frk, i);
	return (status);
}

void	here_doc(int argc, char **argv, char **envp)
{
	t_var	var;
	int		status;

	status = 0;
	var.pipe = (int **)malloc(sizeof(int *) * (argc - 5));
	var.fd0 = open(".tmp", O_CREAT| O_RDWR | O_TRUNC, 0777);
	printf("%s\n", argv[argc - 1]);
	var.fd1 = open(argv[argc - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	put_in_tmp(var.fd0, argv[2]);
	if (var.fd1 == -1)
		perror(argv[argc - 1]);
	var.path = get_path(envp);
	hdoc_uti_parent(&var, argc, envp, argv);
	status = hdoc_uti_parent(&var, argc, envp, argv);
	exit (status);
}
