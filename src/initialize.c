/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:24:05 by pbongiov          #+#    #+#             */
/*   Updated: 2025/09/09 19:44:01 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	_debug(t_table *table)
{
	int	i;

	printf("Philo: %i\n", table->heads);
	printf("Optional: %i\n", table->optional);
	printf("Time to die: %lu\n", table->time_to_die);
	printf("Time to eat: %lu\n", table->time_to_eat);
	printf("Time to sleep: %lu\n", table->time_to_sleep);
	printf("Time passed: %lu\n", table->time);
	i = 0;
	while (i < table->heads)
	{
		printf("==========================\n");
		printf("Philo index: %i\n", table->philo[i].index);
		printf("Philo Last meal: %lu\n", table->philo[i].time_to_live);
		printf("Philo left: %i\n", table->philo[i].left);
		printf("Philo right: %i\n", table->philo[i].right);
		printf("Has_eaten: %i\n", table->philo[i].has_eaten);
		i++;
	}
}

void	data_init(t_table *table, char **av)
{
	int	i;

	i = 0;
	table->heads = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	table->time = 0;
	table->optional = 0;
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
		table->philo[i].has_eaten = 0;
		if (table->philo[i].index % 2)
		{
			table->philo[i].left = i;
			table->philo[i].right = table->philo[i].index % table->heads;
		}
		else
		{
			table->philo[i].left = table->philo[i].index % table->heads;
			table->philo[i].right = i;
		}
		pthread_mutex_init(&table->forks[i], NULL);
		pthread_mutex_init(&table->philo[i].last_meal_mutex, NULL);
		i++;
	}
	//_debug(table);
}
