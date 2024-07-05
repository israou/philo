/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:49:17 by ichaabi           #+#    #+#             */
/*   Updated: 2024/07/05 20:43:38 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	check_arguments(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
	{
		printf("Invalid argument\n");
		return (-1);
	}
	while (i < ac)
	{
		if (check_empty(av[i]) == 1)
			return (-1);
		i++;
	}
	return (0);
}

int	count_splitted_args(t_two_d_arr splitted_args)
{
	int	i;

	i = 0;
	while (splitted_args.s_a[i])
		i++;
	if (i > 5)
	{
		printf("Number of split arguments exceeds the expected limit\n");
		return (-1);
	}
	return (0);
}
