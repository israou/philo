/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 20:09:11 by ichaabi           #+#    #+#             */
/*   Updated: 2024/06/24 17:22:40 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_negative(const char *str)
{
	if (ft_atoi(str) == -2)
		return (-1);
	if (ft_atoi(str) < 0)
	{
		// printf("%d!\n", ft_atoi(str));
		printf("NEEEGAAATIIIVEEE!!!\n");
		return (-1);
	}
	return (0);
}

int	check_empty(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
	{
		printf("Empty argument found\n");
		return (1);
	}
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
	{
		printf("Empty argument found\n");
		return (1);
	}
	return (0);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

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
static int	lenght(char **str, char *del, int size)
{
	int		i;
	int		l;

	i = 0;
	l = 0;
	while (i < size)
	{
		l += ft_strlen(str[i]);
		i++;
	}
	l += ft_strlen(del) * (size - 1);
	return (l);
}

static char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[j])
		j++;
	while (src[i])
	{
		dest[j + i] = src[i];
		i++;
	}
	dest[j + i] = '\0';
	return (dest);
}

char	*ft_strjoin(char **arg, char *del, int size)
{
	char	*result;
	int		i;

	i = 0;
	if (size <= 0)
	{
		result = malloc(sizeof(char));
		if (!result)
			return (NULL);
		result[i] = '\0';
		return (result);
	}
	result = (char *)malloc(sizeof(char) * (lenght(arg, del, size) + 1));
	if (!result)
		return (NULL);
	result[i] = '\0';
	while (i < size)
	{
		ft_strcat(result, arg[i]);
		if (i < size - 1)
			ft_strcat(result, del);
		i++;
	}
	return (result);
}

int	ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strncpy(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (s2[i] && i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
