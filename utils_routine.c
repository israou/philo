/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:41:11 by ichaabi           #+#    #+#             */
/*   Updated: 2024/07/04 23:39:29 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	customized_usleep(int sleep_duration)
{
	long long	current_time;

	current_time = get_the_time();
	while (get_the_time() - current_time < sleep_duration)
		usleep(sleep_duration);
}

void	thinking_process(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->write_mutex);
	printf("%lld %d is thinking\n",
		get_the_time() - philosopher->start_simulation, philosopher->id);
	pthread_mutex_unlock(&philosopher->write_mutex);
}

void	sleeping_process(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->write_mutex);
	printf("%lld %d is sleeping\n",
		get_the_time() - philosopher->start_simulation, philosopher->id);
	pthread_mutex_unlock(&philosopher->write_mutex);
	customized_usleep(philosopher->time_to_sleep);
}

void	eating_process(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->left_fork);
	pthread_mutex_lock(&philosopher->write_mutex);
	printf("%lld %d has taken left fork\n",
		get_the_time() - philosopher->start_simulation, philosopher->id);
	pthread_mutex_unlock(&philosopher->write_mutex);
	pthread_mutex_lock(philosopher->right_fork);
	pthread_mutex_lock(&philosopher->write_mutex);
	printf("%lld %d has taken right fork\n",
		get_the_time() - philosopher->start_simulation, philosopher->id);
	pthread_mutex_unlock(&philosopher->write_mutex);
	pthread_mutex_lock(&philosopher->write_mutex);
	printf("%lld %d is eating\n",
		get_the_time() - philosopher->start_simulation, philosopher->id);
	pthread_mutex_unlock(&philosopher->write_mutex);
	customized_usleep(philosopher->time_to_eat);
	pthread_mutex_lock(&philosopher->meals_increment_mutex);
	philosopher->nb_meals_eaten++;
	pthread_mutex_unlock(&philosopher->meals_increment_mutex);
	pthread_mutex_lock(&philosopher->last_happy_meal_mutex);
	philosopher->last_happy_meal = get_the_time();
	pthread_mutex_unlock(&philosopher->last_happy_meal_mutex);
}

int	n_times_must_eat(t_philosopher *philosopher)
{
	if (philosopher->n_times_m_eat != -1
		&& philosopher->nb_meals_eaten >= philosopher->n_times_m_eat)
	{
		pthread_mutex_lock(philosopher->finished_mutex);
		(*philosopher->finished_eaten)++;
		if (*philosopher->finished_eaten == philosopher->nb_philo)
			return (0);
		pthread_mutex_unlock(philosopher->finished_mutex);
	}
	return (-1);
}
