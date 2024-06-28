/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:23:51 by ichaabi           #+#    #+#             */
/*   Updated: 2024/06/27 23:05:06 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(philosopher_t *philosopher)
{
	int	i;
	int	n;
	int	dead_flag;
	dead_flag = 0;
	pthread_mutex_t	death_check_mutex;
	pthread_mutex_init(&death_check_mutex, NULL);

	i = 0;
	n = philosopher->nb_philo;
	while (i < n)
	{
		philosopher[i].death_check_mutex = &death_check_mutex;
		philosopher[i].dead = &dead_flag;
		pthread_create(&philosopher[i].thread, NULL, routine_process, &philosopher[i]);
		i++;
	}
	pthread_t death_thread;
	pthread_create(&death_thread, NULL, death_checker, philosopher);
	i = 0;
	while (i < n)
	{
		pthread_join(philosopher[i].thread, NULL);
		i++;
	}
	pthread_join(death_thread, NULL);
}



void *death_checker(void *arg)
{
	philosopher_t	*philosophers;
	int	n;
	int	i;

	philosophers = (philosopher_t *)arg;
	n = philosophers[0].nb_philo;
	while (1)
	{
		i = 0;
		while (i < n)
		{
			pthread_mutex_lock(&philosophers[i].last_happy_meal_mutex);
			if (get_the_time() - philosophers[i].last_happy_meal >= philosophers[i].time_to_die)
			{
				pthread_mutex_lock(&philosophers[i].write_mutex);
				printf("%lld %d is died\n", get_the_time() - philosophers[i].start_simulation, philosophers[i].id);
				*(philosophers[i].dead) = 1;
				*(philosophers[i].stop_simulation) = 1;
				pthread_mutex_unlock(&philosophers[i].last_happy_meal_mutex);
				pthread_mutex_unlock(&philosophers[i].write_mutex);
				return NULL;
			}
			pthread_mutex_unlock(&philosophers[i].last_happy_meal_mutex);
			i++;
		}
		customized_usleep(10);
		pthread_mutex_lock(philosophers[0].finished_mutex);
		if (*(philosophers[0].stop_simulation))
		{
			pthread_mutex_unlock(philosophers[0].finished_mutex);
			break;
		}
		pthread_mutex_unlock(philosophers[0].finished_mutex);
	}
	return NULL;
}


void	destroy(philosopher_t *philosopher)
{
	int	i;
	int	n;

	n = philosopher->nb_philo;
	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(philosopher[i].left_fork);
		pthread_mutex_destroy(philosopher[i].right_fork);
		pthread_mutex_destroy(&philosopher[i].meals_increment_mutex);
		pthread_mutex_destroy(&philosopher[i].write_mutex);
		i++;
	}
}
