/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:24:05 by pbongiov          #+#    #+#             */
/*   Updated: 2025/09/18 18:11:29 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	data_init(t_table *table, char **av)
{
	int	i;

	table->heads = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	table->time = 0;
	table->optional = 0;
	table->over = 0;
	table->has_finished = 0;
	if (table->heads < 1 || table->time_to_die < 1 || table->time_to_eat < 1
		|| table->time_to_sleep < 1)
	{
		printf("Arguments must be greater than 0!\n");
		return (2);
	}
	table->philo = malloc(sizeof(t_philo) * (table->heads + 1));
	if (!table->philo)
		return (0);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->heads);
	if (!table->forks)
	{
		free(table->philo);
		return (0);
	}
	i = 0;
	while (i < table->heads)
	{
		table->philo[i].index = i + 1;
		table->philo[i].time_to_live = get_time();
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
		pthread_mutex_init(&table->philo[i].live_mutex, NULL);
		i++;
	}
	pthread_mutex_init(&table->finished_mutex, NULL);
	pthread_mutex_init(&table->over_mutex, NULL);
	pthread_mutex_init(&table->time_mutex, NULL);
	return (1);
}

void	thread_create(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->heads)
	{
		table->philo[i].table = table;
		pthread_create(&table->philo[i].thread_id, NULL, (void *)routine,
			&table->philo[i]);
		i++;
	}
	pthread_create(&table->die_id, NULL, (void *)die, &table);
	pthread_join(table->die_id, NULL);
	i = 0;
	while (i < table->heads)
		pthread_join(table->philo[i++].thread_id, NULL);
}

void	free_stuff(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->heads)
	{
		pthread_mutex_destroy(&table->philo[i].live_mutex);
		pthread_mutex_destroy(&table->philo[i].last_meal_mutex);
		pthread_mutex_destroy(&table->forks[i++]);
	}
	pthread_mutex_destroy(&table->finished_mutex);
	pthread_mutex_destroy(&table->time_mutex);
	pthread_mutex_destroy(&table->over_mutex);
	free(table->philo);
	free(table->forks);
}
