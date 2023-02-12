/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:46:32 by meharit           #+#    #+#             */
/*   Updated: 2023/02/10 23:34:22 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

static int	ft_size(char const *s, char c)
{
	int	i;
	int	word;

	word = 0;
	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{	
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			word++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (word);
}

static char	*ft_word(char const *s, int size)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc(sizeof(char) * (size + 1));
	if (word == NULL)
		return (NULL);
	while (size > i)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	error_free(char **result, int i)
{
	while (i >= 0)
	{
		free(result[i]);
		i--;
	}
}

static void	ft_alloc(char **result, char const *s, char c, int size)
{
	int		alloc;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[j] && i < size)
	{
		alloc = 0;
		while (s[j] && s[j] == c)
			j++;
		while (s[j + alloc] && s[j + alloc] != c)
			alloc++;
		result[i] = ft_word(&s[j], alloc);
		if (result[i] == NULL)
		{
			error_free(result, i);
			free(result);
			return ;
		}
		i++;
		j += alloc;
	}
	result[i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		size;

	if (s == NULL)
		return (NULL);
	size = ft_size(s, c);
	result = (char **)malloc(sizeof(char *) * (size + 1));
	if (result == NULL)
		return (NULL);
	ft_alloc(result, s, c, size);
	return (result);
}
