/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:22:50 by ichaabi           #+#    #+#             */
/*   Updated: 2024/06/23 21:39:54 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	assignin_forks(philosopher_t *philosophers, int n)
{
	int	i;

	i = 0;
	philosophers->nb_philo = n;
	philosophers->fork = malloc(sizeof(pthread_mutex_t) * n);
	if (!philosophers->fork)
	{
		printf("malloc erreur, mutex des fourchettes");
		return (-1);
	}
	while (i < n)//initialiser les mutex dial lforks
	{
		pthread_mutex_init( &philosophers->fork[i], NULL);
		i++;
	}
	i = 0;
	while (i < n)//ncreer les threads pour chaque philo
	{
		philosophers[i].left_fork = &philosophers->fork[i];
		philosophers[i].right_fork = &philosophers->fork[(i + 1) % n];
		i++;
	}
	return (0);
}
