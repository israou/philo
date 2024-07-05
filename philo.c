/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:27:11 by ichaabi           #+#    #+#             */
/*   Updated: 2024/07/05 08:01:35 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int count_splitted_args(t_two_d_arr		splitted_args)
{
	int i = 0;
	while (splitted_args.s_a[i])
		i++;
	if (i > 5)
	{
		printf("Invalid argument..\n");
		return (-1);
	}
	return (0);
}

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
	int				i;

	i = 1;
	if (check_arguments(ac) == -1)
		return (-1);
	while (av[i])
		if (check_empty(av[i++]))
			return(-1);
	splitted_args = check_splitted_args(ac, av);
	if (count_splitted_args(splitted_args) == -1)
		return (-11111);
	n = ft_atoi(av[1]);
	philosopher = allocate_philosopher(n);
	if (!philosopher)
		return (-1);
	if (splitted_args.ret_val == -1)
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
