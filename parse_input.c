/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 20:07:50 by ichaabi           #+#    #+#             */
/*   Updated: 2024/06/24 12:46:56 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	**parse_input(int ac, char **av)
{
	int		i;
	char	**splitted_args;
	i = 1;
	if (ac == 1)
	{
		printf("NOT ENOUGH\n");
		return (NULL);
	}
	while (av[i])
	{
		if (check_empty(av[i]) == 1)
			return (NULL);
		if (check_negative(av[i]) == -1)
			return (NULL);
		i++;
	}
	splitted_args = ft_split(ft_strjoin(av + 1, " ", ac -1), ' ');
	if (splitted_args == NULL)
		return (NULL);
	return (splitted_args);
}

int itterate(char	**splitted_args)
{
	int i = 0;

	int j;
	while (splitted_args[i])
	{
		j = 0;
		while (splitted_args[i][j])
		{
			if (ft_isdigit(splitted_args[i][j]) != 1)
			{
				printf("Argument found is not digit \n");
				return (-2);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_splitted_args(int ac, char **av)
{
	int		i;
	char	**splitted_args;

	i = 0;
	splitted_args = parse_input(ac, av);
	if (!splitted_args)
		return(-2);
	while (splitted_args[i])
	{

		if (ft_atoi(splitted_args[i]) == -2)
			return (-2);
		i++;
	}
	if (itterate(splitted_args) == -2)
		return(-2);
	return (0);
}
