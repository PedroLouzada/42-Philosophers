/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:53:54 by pbongiov          #+#    #+#             */
/*   Updated: 2025/08/30 19:04:50 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_table *table, t_philo *philo)
{
	int left;
	int right;
	
	if (philo->index == 0)
	{
		left = table->heads - 1;
		right = philo->index + 1;
	}
	else if (philo->index == table->heads - 1)
	{
		left = philo->index - 1;
		right = 0;
	}
	else
	{
		left = philo->index - 1;
		right = philo->index + 1;
	}
	table->philo[left].fork = philo->index;
	if (table->philo[left].fork)
	{
		time_passed(table);
		printf("%ld %i has take a fork\n", table->time, philo->index);
	}
	table->philo[right].fork = philo->index;
	if (table->philo[right].fork)
	{
		time_passed(table);
		printf("%ld %i has take a fork\n", table->time, philo->index);
	}
	if (table->philo[left].fork == philo->index && table->philo[right].fork == philo->index)
	{
		time_passed(table);
		printf("%ld %i is eating\n", table->time, philo->index);
	}
	usleep(philo->table->time_to_eat);
	table->philo[left].fork = -1;
	table->philo[right].fork = -1;
}

static void ph_sleep(t_table *table, t_philo *philo)
{
	time_passed(table);
	printf("%ld %i is sleeping\n", table->time, philo->index);
	usleep(table->time_to_sleep);
}
void	*routine(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	while (1)
	{
		pthread_mutex_lock(&philo->lock);
		eat(table, philo);
		pthread_mutex_unlock(&philo->lock);
		ph_sleep(table, philo);
	}
	return (NULL);
}
