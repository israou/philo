/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:23:51 by ichaabi           #+#    #+#             */
/*   Updated: 2024/07/02 23:15:49 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(philosopher_t *philosopher)
{
	int	i;
	int	n;

	i = 0;
	n = philosopher->nb_philo;
	while (i < n)
	{
		pthread_create(&philosopher[i].thread, NULL, routine_process, &philosopher[i]);
		i++;
	}
	i = 0;
	while (i < n)
	{
		pthread_detach(philosopher[i].thread);
		i++;
	}
}



void	death_checker(philosopher_t *philosophers)
{
	int	n;
	int	i;
	int ttsstt = 0;

	n = philosophers[0].nb_philo;
	while (1)
	{
		i = 0;
		while (i < n)
		{
			pthread_mutex_lock(philosophers[i].stop_mutex);
			ttsstt = *(philosophers[i].stop_simulation);
			pthread_mutex_unlock(philosophers[i].stop_mutex);
			if (ttsstt == -11)
				return;
			pthread_mutex_lock(&philosophers[i].last_happy_meal_mutex);
			if (get_the_time() - philosophers[i].last_happy_meal >= philosophers[i].time_to_die)
			{
				pthread_mutex_lock(&philosophers[i].write_mutex);
				printf("%lld %d is died\n", get_the_time() - philosophers[i].start_simulation, philosophers[i].id);
				pthread_mutex_unlock(&philosophers[i].last_happy_meal_mutex);
				pthread_mutex_unlock(&philosophers[i].write_mutex);
				return ;
			}
			pthread_mutex_unlock(&philosophers[i].last_happy_meal_mutex);
			i++;
		}
		customized_usleep(10);
	}
	return ;
}

