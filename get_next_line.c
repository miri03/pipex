/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:22:03 by meharit           #+#    #+#             */
/*   Updated: 2023/02/16 20:34:27 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"
#include "bonus.h"

char	*ft_read(char *string, int fd)
{
	int			rd;
	char		*buff;

	rd = 1;
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buff == NULL)
		return (NULL);
	while (rd > 0 && new_line(string) == 0)
	{
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd == -1)
		{
			free(string);
			free (buff);
			return (NULL);
		}
		buff[rd] = '\0';
		string = ft_strjoin1(string, buff);
	}
	free(buff);
	return (string);
}

char	*ft_line(char *s)
{
	char	*line;
	int		i;
	int		j;


	i = 0;
	j = 0;
	if (s[i] == 0)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i = i + 1;
	line = malloc(sizeof(char) * (i + 1));
	if (line == NULL)
		return (NULL);
	while (s[j] && s[j] != '\n')
	{
		line[j] = s[j];
		j++;
	}
	if (s[j] == '\n')
		line[j++] = '\n';
	line[j] = '\0';
	return (line);
}

char	*ft_remain(char *s)
{
	int		i;
	char	*remain;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\0')
	{
		free(s);
		return (NULL);
	}
	if (s[i] == '\n')
		i++;
	remain = ft_strdup(&s[i]);
	free(s);
	return (remain);
}

char	*get_next_line(int fd)
{
	static char	*string;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	string = ft_read(string, fd);
	if (string == NULL)
		return (NULL);
	line = ft_line(string);
	string = ft_remain(string);
	return (line);
}
