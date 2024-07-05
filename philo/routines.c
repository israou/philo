/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:34:37 by ichaabi           #+#    #+#             */
/*   Updated: 2024/07/04 23:07:06 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	synchronisation(t_philosopher *philosopher)
{
	if (philosopher->id % 2 != 0)
		usleep(100);
}

void	*routine_process(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	synchronisation(philosopher);
	while (1)
	{
		if (n_times_must_eat(philosopher) == 0)
		{
			pthread_mutex_lock(philosopher->stop_mutex);
			*(philosopher->stop_simulation) = -11;
			pthread_mutex_unlock(philosopher->stop_mutex);
			break ;
		}
		eating_process(philosopher);
		pthread_mutex_unlock(philosopher->left_fork);
		pthread_mutex_unlock(philosopher->right_fork);
		thinking_process(philosopher);
		sleeping_process(philosopher);
	}
	return (NULL);
}
