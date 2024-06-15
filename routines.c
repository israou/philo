/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:34:37 by ichaabi           #+#    #+#             */
/*   Updated: 2024/06/15 16:51:38 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	customized_usleep(int sleep_duration)
{
	long long	current_time;

	current_time = get_the_time();
	while (get_the_time() - current_time < sleep_duration)
		usleep(100);
}

//routine_process est l'essence meme du comportement de chaque philosophe

void	*routine_process(void *arg)
{
	philosopher_t *philosopher = (philosopher_t *)arg;
	if (philosopher->id % 2 != 0)
		customized_usleep(10);
	//pour eviter les deadlocks en synchronisant les philosophes

	if (philosopher->nb_philo == 1)
	{
		printf("%lld %d %s\n", get_the_time() - philosopher->start_simulation, philosopher->id, "has taken left fork");
		printf("%lld %d %s\n", get_the_time() - philosopher->start_simulation, philosopher->id, "died");
		pthread_mutex_lock(philosopher->should_die_mutex);
		*philosopher->should_die = 1;
		pthread_mutex_unlock(philosopher->should_die_mutex);
		return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(philosopher->should_die_mutex);
		if (*philosopher->should_die)
		{
			pthread_mutex_unlock(philosopher->should_die_mutex);
			break;
		}
		pthread_mutex_unlock(philosopher->should_die_mutex);
		// philo prend les fourchettes
		pthread_mutex_lock(philosopher->left_fork);//acquisition de la fourchette
		pthread_mutex_lock(&philosopher->write_mutex);
		printf("%lld %d %s\n", get_the_time() - philosopher->start_simulation, philosopher->id, "has taken left fork");
		pthread_mutex_unlock(&philosopher->write_mutex);

		pthread_mutex_lock(philosopher->right_fork);
		pthread_mutex_lock(&philosopher->write_mutex);
		printf("%lld %d %s\n", get_the_time() - philosopher->start_simulation, philosopher->id, "has taken right fork");
		pthread_mutex_unlock(&philosopher->write_mutex);

		//philo mange

		pthread_mutex_lock(&philosopher->write_mutex);
		printf("%lld %d %s\n", get_the_time() - philosopher->start_simulation, philosopher->id, "is eating");
		pthread_mutex_unlock(&philosopher->write_mutex);

		pthread_mutex_lock(&philosopher->meals_increment_mutex);
		philosopher->last_happy_meal = get_the_time();
		pthread_mutex_unlock(&philosopher->meals_increment_mutex);
		customized_usleep(philosopher->time_to_eat);

		pthread_mutex_lock(&philosopher->meals_increment_mutex);
		philosopher->nb_meals_eaten++;

		if (philosopher->n_times_m_eat != -1 && philosopher->nb_meals_eaten >= philosopher->n_times_m_eat)
		{
			pthread_mutex_lock(philosopher->finished_mutex);//le philo a mangé suffisament de repas ghan lockeha pour garantir une operation sure et coherente
			(*philosopher->finished_eaten)++;
			if (*philosopher->finished_eaten == philosopher->nb_philo)//le nbre total de philo ayant mangé == au nbre total de philo
			{
				printf("all philo have eaten at least %d times\n", philosopher->n_times_m_eat);
				pthread_mutex_lock(philosopher->should_die_mutex);
				*philosopher->should_die = 1;
				pthread_mutex_unlock(philosopher->should_die_mutex);
			}
			pthread_mutex_unlock(philosopher->finished_mutex);
		}
		pthread_mutex_unlock(&philosopher->meals_increment_mutex);
//------libere les deux fourchettes
		pthread_mutex_unlock(philosopher->left_fork);//liberation de la fourchette
		pthread_mutex_unlock(philosopher->right_fork);

		//philo pense
		pthread_mutex_lock(&philosopher->write_mutex);
		printf("%lld %d %s\n", get_the_time() - philosopher->start_simulation, philosopher->id, "is thinking");
		pthread_mutex_unlock(&philosopher->write_mutex);


		//philo dort
		pthread_mutex_lock(&philosopher->write_mutex);
		printf("%lld %d %s\n", get_the_time() - philosopher->start_simulation, philosopher->id, "is sleeping");
		customized_usleep(philosopher->time_to_sleep);
		pthread_mutex_unlock(&philosopher->write_mutex);

		check_dead(philosopher);
		//conditions de mort
	}
	return (NULL);
}

void	check_dead(philosopher_t *philosopher)
{
		pthread_mutex_lock(&philosopher->meals_increment_mutex);
		long long time_since_last_meal = get_the_time() - philosopher->last_happy_meal;
		pthread_mutex_unlock(&philosopher->meals_increment_mutex);

		if (time_since_last_meal >= philosopher->time_to_die)
		{
			pthread_mutex_lock(&philosopher->write_mutex);
			printf("%lld %d %s\n", get_the_time() - philosopher->start_simulation, philosopher->id, "died");
			pthread_mutex_unlock(&philosopher->write_mutex);
			pthread_mutex_lock(philosopher->should_die_mutex);
			*philosopher->should_die = 1;
			pthread_mutex_unlock(philosopher->should_die_mutex);
			exit(EXIT_FAILURE);
		}
}
