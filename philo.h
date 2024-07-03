/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:22:55 by ichaabi           #+#    #+#             */
/*   Updated: 2024/07/03 03:07:21 by ichaabi          ###   ########.fr       */
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
	int					*dead;
	pthread_mutex_t		*death_check_mutex;
	pthread_mutex_t		*death_thread;
	int					*stop_simulation;
	pthread_mutex_t		*stop_mutex;
}	t_philosopher;

//-------------------------------parsing
int				ft_atoi(const char *str);
int				operation(const char *str, long long sign, int i);
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
int				assignin_forks(t_philosopher *philosophers, int n);
long long		get_the_time(void);
int				n_times_must_eat(t_philosopher *philosopher);
void			thinking_process(t_philosopher *philosopher);
void			sleeping_process(t_philosopher *philosopher);
void			eating_process(t_philosopher *philosopher);
void			synchronisation(t_philosopher *philosopher);

void			*routine_process(void *arg);
void			customized_usleep(int sleep_duration);

//death
void			death_checker(t_philosopher *philosophers);

void			create_threads(t_philosopher *philosopher);
int				check_negative(const char *str);

//initialisation
t_philosopher	*init_simulation(t_philosopher *philosophers, char **av, int n);
void			init_shared_data(t_philosopher *philosophers, int n);
void			init_philo_attributes(t_philosopher *philo, char **av, int n);
void			init_philo_mutexes(t_philosopher *philosophers, int n);
#endif