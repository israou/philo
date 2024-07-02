/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:34:37 by ichaabi           #+#    #+#             */
/*   Updated: 2024/07/02 23:35:36 by ichaabi          ###   ########.fr       */
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
int	n_times_must_eat(philosopher_t *philosopher)
{
	if (philosopher->n_times_m_eat != -1 && philosopher->nb_meals_eaten >= philosopher->n_times_m_eat)
	{
		pthread_mutex_lock(philosopher->finished_mutex);
		(*philosopher->finished_eaten)++;
		if (*philosopher->finished_eaten == philosopher->nb_philo)
		{
			printf("All philosophers have eaten at least %d times\n", philosopher->n_times_m_eat);
			return (0);
		}
		pthread_mutex_unlock(philosopher->finished_mutex);
	}
	return (-1);
}

void	thinking_process(philosopher_t *philosopher)
{
	pthread_mutex_lock(&philosopher->write_mutex);
	printf("%lld %d is thinking\n", get_the_time() - philosopher->start_simulation, philosopher->id);
	pthread_mutex_unlock(&philosopher->write_mutex);
}

void	sleeping_process(philosopher_t *philosopher)
{
	pthread_mutex_lock(&philosopher->write_mutex);
	printf("%lld %d is sleeping\n", get_the_time() - philosopher->start_simulation, philosopher->id);
	pthread_mutex_unlock(&philosopher->write_mutex);
	customized_usleep(philosopher->time_to_sleep);
}

void	eating_process(philosopher_t *philosopher)
{
	pthread_mutex_lock(philosopher->left_fork);
	pthread_mutex_lock(&philosopher->write_mutex);
	printf("%lld %d has taken left fork\n", get_the_time() - philosopher->start_simulation, philosopher->id);
	pthread_mutex_unlock(&philosopher->write_mutex);
	pthread_mutex_lock(philosopher->right_fork);
	pthread_mutex_lock(&philosopher->write_mutex);
	printf("%lld %d has taken right fork\n", get_the_time() - philosopher->start_simulation, philosopher->id);
	pthread_mutex_unlock(&philosopher->write_mutex);
	pthread_mutex_lock(&philosopher->write_mutex);
	printf("%lld %d is eating\n", get_the_time() - philosopher->start_simulation, philosopher->id);
	pthread_mutex_unlock(&philosopher->write_mutex);
	customized_usleep(philosopher->time_to_eat);
	pthread_mutex_lock(&philosopher->meals_increment_mutex);
	philosopher->nb_meals_eaten++;
	pthread_mutex_unlock(&philosopher->meals_increment_mutex);
	pthread_mutex_lock(&philosopher->last_happy_meal_mutex);
	philosopher->last_happy_meal = get_the_time();
	pthread_mutex_unlock(&philosopher->last_happy_meal_mutex);
}

void	one_philo_process(philosopher_t *philosopher)
{
	pthread_mutex_lock(philosopher->left_fork);
	printf("%lld %d has taken the left fork\n", get_the_time() - philosopher->start_simulation, philosopher->id);
	pthread_mutex_unlock(philosopher->left_fork);
}

void	synchronisation(philosopher_t *philosopher)
{
	if (philosopher->id % 2 != 0)
		usleep(100);
}

void	*routine_process(void *arg)
{
	philosopher_t *philosopher = (philosopher_t *)arg;

	if (philosopher->nb_philo == 1)
	{
		one_philo_process(philosopher);
		return NULL;
	}
	synchronisation(philosopher);
	while (1)
	{
		eating_process(philosopher);
		pthread_mutex_lock(philosopher->stop_mutex);
		if (n_times_must_eat(philosopher) == 0)
		{
			*(philosopher->stop_simulation) = -11;
			pthread_mutex_unlock(philosopher->stop_mutex);
			break;
		}
		pthread_mutex_unlock(philosopher->stop_mutex);
		pthread_mutex_unlock(philosopher->left_fork);
		pthread_mutex_unlock(philosopher->right_fork);
		thinking_process(philosopher);
		sleeping_process(philosopher);
	}
	return NULL;
}
