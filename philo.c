/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:27:11 by ichaabi           #+#    #+#             */
/*   Updated: 2024/06/26 21:18:12 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_shared_data(philosopher_t *philosophers, int n)
{
	int				i;
	int				*finished_count;
	int				*stop_simulation;
	pthread_mutex_t	*finished_mutex;

	i = 0;
	finished_count = malloc(sizeof(int));
	stop_simulation = malloc(sizeof(int));
	finished_mutex = malloc(sizeof(pthread_mutex_t));
	*finished_count = 0;
	*stop_simulation = 0;
	while (i < n)
	{
		philosophers[i].finished_eaten = finished_count;
		philosophers[i].stop_simulation = stop_simulation;
		philosophers[i].finished_mutex = finished_mutex;
		pthread_mutex_init(&philosophers[i].death_check_mutex, NULL);
		i++;
	}
	pthread_mutex_init(finished_mutex, NULL);
}

void	init_philo_attributes(philosopher_t *philo, char **av, int n)
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

void	init_philo_mutexes(philosopher_t *philosophers, int n)
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

philosopher_t	*init_simulation(philosopher_t *philosophers, char **av, int n)
{
	init_shared_data(philosophers, n);
	init_philo_attributes(philosophers, av, n);
	init_philo_mutexes(philosophers, n);
	return (philosophers);
}

int	main(int ac, char **av)
{
	philosopher_t	*philosopher;
	int				n;

	n = ft_atoi(av[1]);
	if (ac < 5 || ac > 6)
	{
		printf("Invalid argument\n");
		return (-1);
	}
	philosopher = malloc(sizeof(philosopher_t) * n);
	if (!philosopher)
	{
		printf("error malloc --> philospher\n");
		return (-1);
	}
	if (check_splitted_args(ac, av) == -2)
	{
		return (-1);
	}
	philosopher = init_simulation(philosopher, av, n);
	if (assignin_forks(philosopher, philosopher->nb_philo) == -1)
		return (-1);
	create_threads(philosopher);
	destroy(philosopher);
}
