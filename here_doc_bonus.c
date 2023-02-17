/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:05:33 by meharit           #+#    #+#             */
/*   Updated: 2023/02/17 20:56:29 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

int	is_lim(char *line, char *lim)
{
	int	i;

	i = 0;
	while (i < ft_strlen(line) - 1)
	{
		if (line[i] == lim[i])
			i++;
		else
			return (0);
	}
	if (i == ft_strlen(lim) && line[i] == '\n')
		return (1);
	return (0);
}

int put_in_tmp(char *lim)
{
	int fd;
	char	*line;

	fd = open(".herdoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		ft_putstr_fd("here_doc> ", 1);
		line = get_next_line(0);
		if (line == NULL)
			break;
		if (is_lim(line, lim))
		{
			free(line);
			break;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	close(fd);
	return (open(".herdoc", O_RDONLY , 0644));
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
	var.fd0 = put_in_tmp(argv[2]);
	var.fd1 = open(argv[argc - 1],O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (var.fd1 == -1)
		perror(argv[argc - 1]);
	var.path = get_path(envp);
	status = hdoc_uti_parent(&var, argc, envp, argv);
	unlink(".herdoc");
	exit (status);
}
