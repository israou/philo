/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:23:51 by ichaabi           #+#    #+#             */
/*   Updated: 2024/07/05 07:52:25 by ichaabi          ###   ########.fr       */
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

int	check_death(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->last_happy_meal_mutex);
	if (get_the_time() - philosopher->last_happy_meal
		>= philosopher->time_to_die)
	{
		mortal_engines(philosopher);
		pthread_mutex_unlock(&philosopher->last_happy_meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philosopher->last_happy_meal_mutex);
	return (0);
}

int	check_stop_simulation(t_philosopher *philosopher)
{
	int	swap;

	pthread_mutex_lock(philosopher->stop_mutex);
	swap = *(philosopher->stop_simulation);
	pthread_mutex_unlock(philosopher->stop_mutex);
	return (swap == -11);
}

void	death_checker(t_philosopher *philosophers)
{
	int	n;
	int	i;

	n = philosophers[0].nb_philo;
	while (1)
	{
		i = 0;
		while (i < n)
		{
			if (check_stop_simulation(&philosophers[i]))
				return ;
			if (check_death(&philosophers[i]))
				return ;
			i++;
		}
		customized_usleep(12);
	}
}
