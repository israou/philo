/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:27:11 by ichaabi           #+#    #+#             */
/*   Updated: 2024/07/03 19:47:06 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lk()
{
	system("leaks philo");
}
int	main(int ac, char **av)
{
	atexit(lk);
	t_philosopher	*philosopher;
	t_two_d_arr		splitted_args;
	int				n;

	n = ft_atoi(av[1]);
	if (ac < 5 || ac > 6)
	{
		printf("Invalid argument\n");
		return (-1);
	}
	philosopher = malloc(sizeof(t_philosopher) * n);
	if (!philosopher)
	{
		printf("error--->malloc");
		return (-1);
	}
	splitted_args = check_splitted_args(ac, av);
	if (splitted_args.ret_val == -2)
	{
		freee(splitted_args.s_a);
		free(philosopher);
		return (-1);
	}
	freee(splitted_args.s_a);
	philosopher = init_simulation(philosopher, av, n);
	if (assignin_forks(philosopher, philosopher->nb_philo) == -1)
	{
		free(philosopher);
		return (-1);
	}
	create_threads(philosopher);
	death_checker(philosopher);
}
