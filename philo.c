/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:27:11 by ichaabi           #+#    #+#             */
/*   Updated: 2024/07/04 16:58:23 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philosopher	*allocate_philosopher(int n)
{
	t_philosopher	*philosopher;

	philosopher = malloc(sizeof(t_philosopher) * n);
	if (!philosopher)
	{
		printf("error--->malloc");
		return (NULL);
	}
	return (philosopher);
}

int	main(int ac, char **av)
{
	t_philosopher	*philosopher;
	t_two_d_arr		splitted_args;
	int				n;

	n = ft_atoi(av[1]);
	if (check_arguments(ac) == -1)
		return (-1);
	philosopher = allocate_philosopher(n);
	if (!philosopher)
		return (-1);
	splitted_args = check_splitted_args(ac, av);
	if (splitted_args.ret_val == -2)
	{
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
