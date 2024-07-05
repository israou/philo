/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:40:42 by ichaabi           #+#    #+#             */
/*   Updated: 2024/07/03 02:25:23 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_the_time(void)
{
	struct timeval	now;
	long long		time;

	gettimeofday(&now, NULL);
	time = (now.tv_sec * 1000LL) + (now.tv_usec / 1000LL);
	return (time);
}
