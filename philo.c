/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:27:11 by ichaabi           #+#    #+#             */
/*   Updated: 2024/07/03 03:07:21 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philosopher	*philosopher;
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
		printf("error malloc --> philospher\n");
		return (-1);
	}
	if (check_splitted_args(ac, av) == -2)
	{
		return (-1);
	}
	philosopher = init_simulation(philosopher, av, n);
	if (assignin_forks(philosopher, philosopher->nb_philo) == -1)
		return (-1);
	create_threads(philosopher);
	death_checker(philosopher);
}
