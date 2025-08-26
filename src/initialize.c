/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:24:05 by pbongiov          #+#    #+#             */
/*   Updated: 2025/08/26 17:36:29 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief Initialize all global values
void	data_init(t_table *table, char **av)
{
	table->forks = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	if (table->forks < 1 || table->time_to_die < 1 || table->time_to_eat < 1
		|| table->time_to_sleep < 1)
	{
		printf("Arguments should be greater than 0!\n");
		exit(0);
	}
	table->philo = malloc(sizeof(t_philo) * (table->forks + 1));
	if (!table->philo)
		exit(0);
}
