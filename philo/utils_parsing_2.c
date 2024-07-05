/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:02:39 by ichaabi           #+#    #+#             */
/*   Updated: 2024/07/03 19:37:24 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	int	i;

	i = 0;
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
