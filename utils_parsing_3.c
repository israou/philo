/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:03:04 by ichaabi           #+#    #+#             */
/*   Updated: 2024/07/04 23:07:06 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	count_words(char *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			while (s[i] && s[i] != c)
				i++;
			words++;
		}
	}
	return (words);
}

static int	len_of_word(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	*free_split(char **output, int words)
{
	while (words)
	{
		free(output[words -1]);
		words--;
	}
	free(output);
	return (NULL);
}

static char	**allocation(char *s, char c)
{
	char	**output;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	output = (char **)malloc((words + 1) * sizeof(char *));
	if (!output)
		return (NULL);
	output[words] = NULL;
	return (output);
}

char	**ft_split(char *s, char c)
{
	char	**output;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	output = allocation(s, c);
	if (!output)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			len = len_of_word((s + i), c);
			output[j] = (char *)malloc((len + 1) * sizeof(char));
			if (!output[j])
				return (free_split(output, count_words(s, c)));
			ft_strncpy(output[j++], (s + i), len);
			i = i + len;
		}
	}
	return (output);
}
