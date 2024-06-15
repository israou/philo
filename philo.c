/* ************************************************************************** */
/*                                           b                                  */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:27:11 by ichaabi           #+#    #+#             */
/*   Updated: 2024/06/13 17:08:20 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_simulation(philosopher_t *philosophers, char **av, int n)
{
	int	i;
	int	*should_die = malloc(sizeof(int));
	should_die = 0;

	// pthread_mutex_t	*should_die_mutex = malloc(sizeof(pthr));
	// pthread_mutex_init(should_die_mutex, NULL);
	i = 0;
	while (i < n)
	{
		philosophers[i].id = i + 1; //l operateur . accede a un element specifique il agit comme index mais il represente une structure
		// philosophers[i].state = THINKING;
		philosophers[i].nb_philo = ft_atoi(av[1]);
		philosophers[i].time_to_die = ft_atoi(av[2]);
		philosophers[i].time_to_eat = ft_atoi(av[3]);
		philosophers[i].time_to_sleep = ft_atoi(av[4]);
		philosophers[i].n_times_m_eat = (av[5])? ft_atoi(av[5]) : -1;
		philosophers[i].nb_meals_eaten = 0;
		philosophers[i].start_simulation = get_the_time();
		philosophers[i].last_happy_meal = get_the_time();
		pthread_mutex_init(&philosophers[i].write_mutex, NULL);
		pthread_mutex_init(&philosophers[i].meals_increment_mutex, NULL);

		i++;
	}

}

philosopher_t	*initialize_mutexes(philosopher_t *philosophers, int n)
{
	int i = 0;

	int				*finished_count = malloc(sizeof(int));
	*finished_count = 0;
	pthread_mutex_t	*finished_mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(finished_mutex, NULL);

	int				*should_die = malloc(sizeof(int));
	*should_die = 0;
	pthread_mutex_t	*should_die_mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(should_die_mutex, NULL);
	while (i < n)
	{
		// initialize_simulation(philosophers, av, n);
		philosophers[i].finished_eaten = finished_count;//new
		philosophers[i].finished_mutex = finished_mutex;
		philosophers[i].should_die = should_die;
		philosophers[i].should_die_mutex = should_die_mutex;
		i++;
	}
	return (philosophers);
}

int main(int ac, char **av)
{
	int	i;

	i = 0;
	int n = ft_atoi(av[1]);
	if (ac < 5 || ac > 6)
		errors("invalid number of aguments");
	philosopher_t *philosopher = malloc(sizeof(philosopher_t) * n);
	if (!philosopher)
		errors("erreur malloc main philosopher");


	// // int philosophers_finished_eating = 0;
	// pthread_mutex_t finished_mutex;


	philosopher[i].nb_philo = ft_atoi(av[1]);
	philosopher[i].time_to_die = ft_atoi(av[2]);
	philosopher[i].time_to_eat = ft_atoi(av[3]);
	philosopher[i].time_to_sleep = ft_atoi(av[4]);
	philosopher[i].n_times_m_eat = (av[5])? ft_atoi(av[5]) : -1;
	check_splitted_args(ac, av);

	initialize_simulation(philosopher, av, n);
	philosopher = initialize_mutexes(philosopher, n);

	assignin_forks(philosopher, philosopher->nb_philo);

	i = 0;
	while (i < n)
	{
		pthread_create(&philosopher[i].thread, NULL, routine_process, &philosopher[i]);
		i++;
	}
	i = 0;
	while (i < n)
	{
		pthread_join(philosopher[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(philosopher[i].left_fork);
		pthread_mutex_destroy(philosopher[i].right_fork);
		pthread_mutex_destroy(&philosopher[i].meals_increment_mutex);
		pthread_mutex_destroy(&philosopher[i].write_mutex);
		pthread_mutex_destroy(philosopher[0].finished_mutex);
		pthread_mutex_destroy(philosopher[0].should_die_mutex);
		i++;
	}

}
