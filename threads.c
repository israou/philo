/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:23:51 by ichaabi           #+#    #+#             */
/*   Updated: 2024/07/04 01:51:57 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_philosopher *philosopher)
{
	int	i;
	int	n;

	i = 0;
	n = philosopher->nb_philo;
	while (i < n)
	{
		pthread_create(&philosopher[i].thread, NULL, routine_process,
			&philosopher[i]);
		i++;
	}
	i = 0;
	while (i < n)
	{
		pthread_detach(philosopher[i].thread);
		i++;
	}
}

void	mortal_engines(t_philosopher *philosophers)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philosophers[i].write_mutex);
	printf("%lld %d is died\n",
		get_the_time() - philosophers[i].start_simulation, philosophers[i].id);
	pthread_mutex_unlock(&philosophers[i].last_happy_meal_mutex);
	pthread_mutex_unlock(&philosophers[i].write_mutex);
}

void	death_checker(t_philosopher *philosophers)
{
	int	n;
	int	i;
	int	swap;

	swap = 0;
	n = philosophers[0].nb_philo;
	while (1)
	{
		i = 0;
		while (i < n)
		{
			pthread_mutex_lock(philosophers[i].stop_mutex);
			swap = *(philosophers[i].stop_simulation);
			pthread_mutex_unlock(philosophers[i].stop_mutex);
			if (swap == -11)
				return ;
			pthread_mutex_lock(&philosophers[i].last_happy_meal_mutex);
			if (get_the_time() - philosophers[i].last_happy_meal
				>= philosophers[i].time_to_die)
			{
				mortal_engines(&philosophers[i]);
				return ;
			}
			pthread_mutex_unlock(&philosophers[i].last_happy_meal_mutex);
			i++;
		}
		customized_usleep(15);
	}
	return ;
}
