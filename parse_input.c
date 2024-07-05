/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 20:07:50 by ichaabi           #+#    #+#             */
/*   Updated: 2024/07/05 08:00:19 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_two_d_arr parse_input(int ac, char **av)
{
	int		i;
	t_two_d_arr sa;
	char	*tmp;

	tmp = ft_strjoin(av + 1, " ", ac -1);
	sa.s_a = ft_split(tmp, ' ');
	sa.ret_val = 0;
	if (sa.s_a == NULL)
	{
		sa.ret_val = -1;
		return (sa);
	}
	i = 0;
	while (sa.s_a[i])
	{
		if (ft_atoi(sa.s_a[i]) == 777 && ft_atoi(av[i + 1]) == 777)
			return (sa);
		else if (check_empty(sa.s_a[i]) == 1)
		{
			sa.ret_val = -1;
			freee(sa.s_a);
			return (sa);
		}
		else if (ft_atoi(sa.s_a[i]) < 0)
		{
			printf("NEEEGAAATIIIVEEE!\n");
			printf("%lld", ft_atoi(sa.s_a[i]));
			sa.ret_val = -1;
			freee(sa.s_a);
			return (sa);
		}
		i++;
	}
	free(tmp);
	return (sa);
}

int	itterate(char **splitted_args)
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
				return (-1);
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
	t_two_d_arr	splitted_args;

	i = 0;
	splitted_args = parse_input(ac, av);
	if (!splitted_args.s_a || splitted_args.ret_val == -1)
	{
		splitted_args.ret_val = -1;
		return (splitted_args);
	}
	while (splitted_args.s_a[i])
	{
		if (itterate(splitted_args.s_a) == -1)
		{
			splitted_args.ret_val = -1;
			freee(splitted_args.s_a);
			return (splitted_args);
		}
		i++;
	}
	return (splitted_args);
}
