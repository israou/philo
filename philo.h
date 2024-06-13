/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:22:55 by ichaabi           #+#    #+#             */
/*   Updated: 2024/06/12 16:16:16 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <limits.h>

typedef enum {THINKING, EATING, SLEEPING, DEAD} PHILOSOPHER_STATE;
typedef struct philosopher
{
	int					id; // id du philosophe
	pthread_t			thread; // thread de chaque philosophe
	pthread_mutex_t		*left_fork; //mutex de la fourchette gauche
	pthread_mutex_t		*right_fork; //mutex de la fourchette droite
	PHILOSOPHER_STATE	state;
	int					nb_meals_eaten; //nbr de repas mangés
	pthread_mutex_t		meals_increment_mutex; //incrementations du nbre de repas mangé
	int					time_to_die;
	int					time_to_sleep;
	int					time_to_eat;
	int					n_times_m_eat; //n fois min pour manger
	int					nb_philo; //nbre de philosophes
	pthread_mutex_t	*fork; //tableau de mutex ela qbel les fourchettes;
	long long				start_simulation;
	long				last_happy_meal; //lweqt dial akhir repas
	pthread_mutex_t		write_mutex;
	int					*finished_eaten;
	pthread_mutex_t		*finished_mutex;
} philosopher_t;


//-------------------------------
int			ft_atoi(const char *str);
void		errors(char	*str);
int			is_int(char *str);
int			ft_strlen(char *str);
char		**ft_split(char *s, char c);
char		*ft_strjoin(char **arg, char *del, int size);
int			check_empty(const char *str);
void		free_memory(char **args);
char		**parse_input(int ac, char **av);
void		check_splitted_args(int ac, char **av);

philosopher_t	*initialize_simulation(philosopher_t *philosophers, char **av, int n, int *finished_count, pthread_mutex_t *finished_mutex);

void		assignin_forks(philosopher_t *philosophers, int n);
long long	get_the_time(void);
void		*routine_process(void *arg);
char		*ft_strncpy(char *s1, char *s2, int n);
int			ft_isdigit(char c);

void	check_dead(philosopher_t *philosopher, int n);

///////
// void	usleep(int sleep_duration);
//////

#endif
