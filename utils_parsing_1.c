/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:49:17 by ichaabi           #+#    #+#             */
/*   Updated: 2024/07/04 16:58:19 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_negative(const char *str)
{
	if (ft_atoi(str) == -2)
		return (-1);
	if (ft_atoi(str) < 0)
	{
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

int	check_arguments(int ac)
{
	if (ac < 5 || ac > 6)
	{
		printf("Invalid argument\n");
		return (-1);
	}
	return (0);
}
