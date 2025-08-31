/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:24:05 by pbongiov          #+#    #+#             */
/*   Updated: 2025/08/31 19:10:39 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief Initialize all global values
void	data_init(t_table *table, char **av)
{
	int i;

	i = 0;
	table->heads = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1000;
	table->time_to_eat = ft_atol(av[3]) * 1000;
	table->time_to_sleep = ft_atol(av[4]) * 1000;
	if (table->heads < 1 || table->time_to_die < 1 || table->time_to_eat < 1
		|| table->time_to_sleep < 1)
	{
		printf("Arguments must be greater than 0!\n");
		exit(0);
	}
	table->philo = malloc(sizeof(t_philo) * (table->heads + 1));
	if (!table->philo)
		exit(0);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->heads);
	if (!table->forks)
	{
		free(table->philo);
		exit(0);
	}
	while (i < table->heads)
	{
		table->philo[i].index = i + 1;
		pthread_mutex_init(&table->forks[i++], NULL);
	}
}
