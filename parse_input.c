/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 20:07:50 by ichaabi           #+#    #+#             */
/*   Updated: 2024/06/11 15:16:53 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	**parse_input(int ac, char **av)
{
	int		i;
	char	**splitted_args;
	i = 0;
	while (av[++i])
		if (check_empty(av[i]))
			errors("empty");
	splitted_args = ft_split(ft_strjoin(av + 1, " ", ac -1), ' ');
	if (splitted_args == NULL)
		errors("error join or split splitted_args");
	return (splitted_args);
}

void	check_splitted_args(int ac, char **av)
{
	int		i;
	int		j;
	char	**splitted_args;

	i = 0;
	j = 0;
	splitted_args = parse_input(ac, av);
	while (splitted_args[i])
	{
		if (ft_atoi(splitted_args[i]) < 0)
			errors("negative!!!!");
		i++;
	}
	i = 0;
	while (splitted_args[i])
	{
		j = 0;
		while (splitted_args[i][j])
		{
			if (ft_isdigit(splitted_args[i][j]) != 1)
				errors("not DIGGGIIIT!!!!");
			j++;
		}
		i++;
	}
}
