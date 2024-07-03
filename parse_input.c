/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 20:07:50 by ichaabi           #+#    #+#             */
/*   Updated: 2024/07/03 19:38:26 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	**parse_input(int ac, char **av)
{
	int		i;
	char	**splitted_args;
	char	*tmp;

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
	tmp = ft_strjoin(av + 1, " ", ac -1);
	splitted_args = ft_split(tmp, ' ');
	free(tmp);
	if (splitted_args == NULL)
		return (NULL);
	return (splitted_args);
}

int	itterate(char	**splitted_args)
{
	int	i;
	int	j;

	i = 0;
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

t_two_d_arr	check_splitted_args(int ac, char **av)
{
	int			i;
	int			j;
	t_two_d_arr	splitted_args;

	i = 0;
	j = 0;
	splitted_args.ret_val = 0;
	splitted_args.s_a = parse_input(ac, av);
	if (!splitted_args.s_a)
	{
		splitted_args.ret_val = -2;
		return (splitted_args);
	}
	while (splitted_args.s_a[i])
	{
		if (ft_atoi(splitted_args.s_a[i]) == -2)
		{
			splitted_args.ret_val = -2;
			return (splitted_args);
		}
		i++;
	}
	if (itterate(splitted_args.s_a) == -2)
	{
		splitted_args.ret_val = -2;
		return (splitted_args);
	}
	return (splitted_args);
}
