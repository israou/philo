/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 06:18:52 by ichaabi           #+#    #+#             */
/*   Updated: 2024/07/05 20:19:51 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	freee(char **output)
{
	int	i;

	i = 0;
	if (!output)
		return ;
	while (output[i])
	{
		free(output[i]);
		i++;
	}
	free(output);
}
