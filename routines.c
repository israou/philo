/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:34:37 by ichaabi           #+#    #+#             */
/*   Updated: 2024/06/12 20:43:47 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//routine_process est l'essence meme du comportement de chaque philosophe
void	*routine_process(void *arg)
{
	philosopher_t *philosopher = (philosopher_t *)arg;
	if (philosopher->id % 2 != 0)
		usleep(100);
	//pour eviter les deadlocks en synchronisant les philosophes
	if (philosopher->nb_philo == 1)
	{
		philosopher->state = DEAD;
		printf("%lld %d %s\n", get_the_time() - philosopher->start_simulation, philosopher->id, "has taken left fork");
		printf("%lld %d %s\n", get_the_time() - philosopher->start_simulation, philosopher->id, "died");
	}
	while (philosopher->state != DEAD)
	{
		pthread_mutex_lock(philosopher->left_fork);//acquisition de la fourchette
		printf("%lld %d %s\n", get_the_time() - philosopher->start_simulation, philosopher->id, "has taken left fork");

		pthread_mutex_lock(philosopher->right_fork);
		printf("%lld %d %s\n", get_the_time() - philosopher->start_simulation, philosopher->id, "has taken right fork");

		printf("%lld %d %s\n", get_the_time() - philosopher->start_simulation, philosopher->id, "is eating");
		usleep(philosopher->time_to_eat * 1000);

		pthread_mutex_lock(&philosopher->meals_increment_mutex);
		philosopher->nb_meals_eaten++;
		philosopher->last_happy_meal = get_the_time();

		if (philosopher->n_times_m_eat != -1 && philosopher->nb_meals_eaten >= philosopher->n_times_m_eat)
		{
			pthread_mutex_lock(philosopher->finished_mutex);//le philo a mangé suffisament de repas ghan lockeha pour garantir une operation sure et coherente
			(*philosopher->finished_eaten)++;
			if (*philosopher->finished_eaten == philosopher->nb_philo)//le nbre total de philo ayant mangé == au nbre total de philo
			{
				printf("all philo have eaten at least %d times\n", philosopher->n_times_m_eat);
				exit(0);
			}
			pthread_mutex_unlock(philosopher->finished_mutex);
		}
		pthread_mutex_unlock(&philosopher->meals_increment_mutex);

		pthread_mutex_unlock(philosopher->left_fork);//liberation de la fourchette
		pthread_mutex_unlock(philosopher->right_fork);


		printf("%lld %d %s\n", get_the_time() - philosopher->start_simulation, philosopher->id, "is sleeping");
		usleep(philosopher->time_to_sleep * 1000);

		printf("%lld %d %s\n", get_the_time() - philosopher->start_simulation, philosopher->id, "is thinking");
		check_dead(philosopher, philosopher->nb_philo);
	}
	return (NULL);
}

void	check_dead(philosopher_t *philosopher, int n)
{
	int i = 0;
	long current_time;

	while (i < n)
	{
		current_time = get_the_time();
		if (current_time - philosopher->last_happy_meal > philosopher->time_to_die)
		{
			philosopher->state = DEAD;
			printf("%lld %d %s\n", current_time - philosopher->start_simulation, philosopher->id, "died");
			exit(EXIT_FAILURE);
		}
		// if (philosopher[i].n_times_m_eat != -1 && philosopher[i].nb_meals_eaten >= philosopher[i].n_times_m_eat)
		// {
		// 	philosopher->state = DEAD;
		// 	printf("%lld %d %s\n", current_time - philosopher->start_simulation, philosopher->id, "died");
		// 	exit(EXIT_FAILURE);
		// }
		if (philosopher->time_to_eat > philosopher->time_to_die)
		{
			philosopher->state = DEAD;
			printf("%lld %d %s\n", current_time - philosopher->start_simulation, philosopher->id, "died");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
