/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:27:11 by ichaabi           #+#    #+#             */
/*   Updated: 2024/07/05 21:24:21 by ichaabi          ###   ########.fr       */
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

int	handle_errors_and_free(t_two_d_arr s_a, t_philosopher *philo)
{
	freee(s_a.s_a);
	if (philo)
		free(philo);
	return (-11111);
}

int	main(int ac, char **av)
{
	t_philosopher	*philosopher;
	t_two_d_arr		splitted_args;
	int				n;

	if (check_arguments(ac, av) == -1)
		return (-1);
	splitted_args = check_splitted_args(ac, av);
	if (splitted_args.ret_val == -1 || count_splitted_args(splitted_args) == -1)
		return (handle_errors_and_free(splitted_args, NULL));
	philosopher = initialize_philos(av, splitted_args, &n);
	if (!philosopher)
		return (handle_errors_and_free(splitted_args, philosopher));
	create_threads(philosopher);
	death_checker(philosopher);
}
