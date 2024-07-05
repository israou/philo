/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:07:27 by ichaabi           #+#    #+#             */
/*   Updated: 2024/07/05 21:24:16 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_shared_data(t_philosopher *philosophers, int n)
{
	int				i;
	int				*finished_count;
	int				*stop_simulation;
	pthread_mutex_t	*finished_mutex;
	pthread_mutex_t	*stop_mutex;

	i = 0;
	finished_count = malloc(sizeof(int));
	stop_simulation = malloc(sizeof(int));
	finished_mutex = malloc(sizeof(pthread_mutex_t));
	stop_mutex = malloc(sizeof(pthread_mutex_t));
	*finished_count = 0;
	*stop_simulation = 0;
	pthread_mutex_init(finished_mutex, NULL);
	pthread_mutex_init(stop_mutex, NULL);
	while (i < n)
	{
		philosophers[i].finished_eaten = finished_count;
		philosophers[i].stop_simulation = stop_simulation;
		philosophers[i].finished_mutex = finished_mutex;
		philosophers[i].stop_mutex = stop_mutex;
		i++;
	}
}

void	init_philo_attributes(t_philosopher *philo, char **av, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		philo[i].id = i + 1;
		philo[i].nb_philo = ft_atoi(av[1]);
		philo[i].time_to_die = ft_atoi(av[2]);
		philo[i].time_to_eat = ft_atoi(av[3]);
		philo[i].time_to_sleep = ft_atoi(av[4]);
		if (av[5])
		{
			philo[i].n_times_m_eat = ft_atoi(av[5]);
		}
		else
		{
			philo[i].n_times_m_eat = -1;
		}
		philo[i].nb_meals_eaten = 0;
		philo[i].start_simulation = get_the_time();
		philo[i].last_happy_meal = get_the_time();
		i++;
	}
}

void	init_philo_mutexes(t_philosopher *philosophers, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_init(&philosophers[i].last_happy_meal_mutex, NULL);
		pthread_mutex_init(&philosophers[i].write_mutex, NULL);
		pthread_mutex_init(&philosophers[i].meals_increment_mutex, NULL);
		i++;
	}
}

t_philosopher	*init_simulation(t_philosopher *philosophers, char **av, int n)
{
	init_shared_data(philosophers, n);
	init_philo_attributes(philosophers, av, n);
	init_philo_mutexes(philosophers, n);
	return (philosophers);
}

t_philosopher	*initialize_philos(char **av, t_two_d_arr s_a, int *n)
{
	t_philosopher	*philosopher;

	*n = ft_atoi(av[1]);
	philosopher = allocate_philosopher(*n);
	if (!philosopher || s_a.ret_val == -1)
		return (NULL);
	freee(s_a.s_a);
	philosopher = init_simulation(philosopher, av, *n);
	if (assignin_forks(philosopher, philosopher->nb_philo) == -1)
	{
		free(philosopher);
		return (NULL);
	}
	return (philosopher);
}
