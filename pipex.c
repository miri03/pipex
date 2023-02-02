/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:37:32 by meharit           #+#    #+#             */
/*   Updated: 2023/02/02 21:32:42 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
	t_var	var;

	if (argc != 5)
		error_message("Not enought/too much arguments\n");
	var.fd = open(argv[1], O_RDONLY);
	var.fd1 = open(argv[1], O_RDONLY);
	if (fd == -1)
		perror(argv[1]);
	var.path = get_path(envp);
//	does_exist(char *path_c, char **path)
}
