/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:22:55 by ichaabi           #+#    #+#             */
/*   Updated: 2024/06/27 15:00:44 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>
# include <limits.h>

typedef struct philosopher
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	int					nb_meals_eaten;
	pthread_mutex_t		meals_increment_mutex;
	int					time_to_die;
	int					time_to_sleep;
	int					time_to_eat;
	int					n_times_m_eat;
	int					nb_philo;
	pthread_mutex_t		*fork;
	long long			start_simulation;
	long long			last_happy_meal;
	pthread_mutex_t		last_happy_meal_mutex;
	pthread_mutex_t		write_mutex;
	int					*finished_eaten;
	pthread_mutex_t		*finished_mutex;
	pthread_mutex_t		death_check_mutex;
	pthread_mutex_t		*death_thread;
	int					*stop_simulation;
	int					*stop;
	pthread_mutex_t		*stop_mutex;
}	philosopher_t;

//-------------------------------parsing
int				ft_atoi(const char *str);
int				ft_strlen(char *str);
char			**ft_split(char *s, char c);
char			*ft_strjoin(char **arg, char *del, int size);
int				check_empty(const char *str);
void			free_memory(char **args);
char			**parse_input(int ac, char **av);
int				check_splitted_args(int ac, char **av);
char			*ft_strncpy(char *s1, char *s2, int n);
int				ft_isdigit(char c);
int				itterate(char	**splitted_args);

//for routine
int				assignin_forks(philosopher_t *philosophers, int n);
long long		get_the_time(void);
void			*routine_process(void *arg);
void			customized_usleep(int sleep_duration);
void		thinking_process(philosopher_t *philosopher);
void		sleeping_process(philosopher_t *philosopher);
//death
void			*death_checker(void *arg);

//threads
void			destroy(philosopher_t *philosopher);
void			create_threads(philosopher_t *philosopher);
int				check_negative(const char *str);

//initialisation
philosopher_t	*init_simulation(philosopher_t *philosophers, char **av, int n);
void			init_shared_data(philosopher_t *philosophers, int n);
void			init_philo_attributes(philosopher_t *philo, char **av, int n);
void			init_philo_mutexes(philosopher_t *philosophers, int n);

#endif