/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:35:24 by ichaabi           #+#    #+#             */
/*   Updated: 2024/07/03 02:24:04 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	operation(const char *str, long long sign, int i)
{
	long long	res;

	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	if ((res * sign) > 2147483647 || (res * sign) < -2147483648)
	{
		printf("Number out of range\n");
		return (-2);
	}
	return (res);
}

int	ft_atoi(const char *str)
{
	int			i;
	long long	sign;
	long long	res;

	res = 0;
	i = 0;
	sign = 1;
	if (!str)
		return (-2);
	if (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
		if (str[i] == '-' || str[i] == '+')
		{
			printf("too much signs\n");
			return (-2);
		}
	}
	res = operation(str, sign, i);
	return (res * sign);
}

void	errors(char	*str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}
