/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:34:37 by ichaabi           #+#    #+#             */
/*   Updated: 2024/07/02 03:59:58 by ichaabi          ###   ########.fr       */
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
			// *(philosopher->stop_simulation) = 1;
		}
		pthread_mutex_unlock(philosopher->finished_mutex);
	}
	return (-1);
}
void	sleeping_process(philosopher_t *philosopher)
{
	pthread_mutex_lock(&philosopher->write_mutex);
	printf("%lld %d is sleeping\n", get_the_time() - philosopher->start_simulation, philosopher->id);
	pthread_mutex_unlock(&philosopher->write_mutex);
	customized_usleep(philosopher->time_to_sleep);
}

void *routine_process(void *arg)
{
	philosopher_t *philosopher = (philosopher_t *)arg;

	if (philosopher->nb_philo == 1)
	{
		pthread_mutex_lock(philosopher->left_fork);
		printf("%lld %d has taken the left fork\n", get_the_time() - philosopher->start_simulation, philosopher->id);
		pthread_mutex_unlock(philosopher->left_fork);
		return NULL;
	}
	if (philosopher->id % 2 != 0)
		usleep(100);
	while (1)
	{
		// pthread_mutex_lock(&philosopher->write_mutex);
		// if (*(philosopher->stop_simulation))
		// {
		// 	pthread_mutex_unlock(&philosopher->write_mutex);
		// 	break;
		// }
		// pthread_mutex_unlock(&philosopher->write_mutex);
//eating :
		pthread_mutex_lock(philosopher->left_fork);
		// if (*(philosopher->stop_simulation))
		// {
		// 	pthread_mutex_unlock(&philosopher->write_mutex);
		// 	pthread_mutex_unlock(philosopher->left_fork);
		// 	break;
		// }
		pthread_mutex_lock(&philosopher->write_mutex);
		printf("%lld %d has taken left fork\n", get_the_time() - philosopher->start_simulation, philosopher->id);
		pthread_mutex_unlock(&philosopher->write_mutex);

		pthread_mutex_lock(philosopher->right_fork);
		// if (*(philosopher->stop_simulation))
		// {
		// 	pthread_mutex_unlock(&philosopher->write_mutex);
		// 	pthread_mutex_unlock(philosopher->right_fork);
		// 	pthread_mutex_unlock(philosopher->left_fork);
		// 	break;
		// }
		pthread_mutex_lock(&philosopher->write_mutex);
		printf("%lld %d has taken right fork\n", get_the_time() - philosopher->start_simulation, philosopher->id);
		pthread_mutex_unlock(&philosopher->write_mutex);

		pthread_mutex_lock(&philosopher->write_mutex);
		printf("%lld %d is eating\n", get_the_time() - philosopher->start_simulation, philosopher->id);
		pthread_mutex_unlock(&philosopher->write_mutex);
		customized_usleep(philosopher->time_to_eat);

		pthread_mutex_lock(&philosopher->meals_increment_mutex);
		philosopher->nb_meals_eaten++;
		pthread_mutex_lock(&philosopher->last_happy_meal_mutex);
		philosopher->last_happy_meal = get_the_time();
		pthread_mutex_unlock(&philosopher->last_happy_meal_mutex);
//n_times_must_eat:
		if (n_times_must_eat(philosopher) == 0)
		{
			// pthread_mutex_lock(&philosopher->write_mutex);
			*(philosopher->stop_simulation) = -11;
			// pthread_mutex_unlock(&philosopher->write_mutex);
			break;
		}
		pthread_mutex_unlock(&philosopher->meals_increment_mutex);

		pthread_mutex_unlock(philosopher->left_fork);
		pthread_mutex_unlock(philosopher->right_fork);

		if (*(philosopher->stop_simulation))
		{
			break ;
		}
//thinking:
		pthread_mutex_lock(&philosopher->write_mutex);
		printf("%lld %d is thinking\n", get_the_time() - philosopher->start_simulation, philosopher->id);
		pthread_mutex_unlock(&philosopher->write_mutex);
//sleeping:
		sleeping_process(philosopher);
//condition de mort:
	}
	return NULL;
}
